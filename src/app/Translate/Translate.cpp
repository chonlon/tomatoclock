#include "Translate.h"

#include <QCryptographicHash>
#include <QNetWorkReply>
#include <QJsonDocument>
#include <QtWidgets/QLineEdit>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QFocusEvent>
#include <algorithm>
#include <cassert>
static int translate_box_height = 70;

enum HOT_KEY_ID {
    ACTIVE_WINDOW
};

#define  APP_KEY "4e7ef943af307886"
#define  APP_SECRET "V742c09iOArGyM4eNyloBCqls7Ba1NKL"

Translate::Translate(QWidget* parent)
    : QWidget(parent) {
    this->setWindowOpacity(0.6);
    vertical_layout_p_ = new QVBoxLayout(this);
    line_edit_p_ = new QLineEdit(this);

    QFont font;
    font.setFamily(QString::fromUtf8("Microsoft YaHei"));
    font.setPointSize(18);
    line_edit_p_->setFont(font);
    line_edit_p_->setDragEnabled(true);

    vertical_layout_p_->setContentsMargins(0, 0, 0, 0);
    line_edit_p_->setFixedHeight(translate_box_height);
    line_edit_p_->installEventFilter(this);

    vertical_layout_p_->addWidget(line_edit_p_);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
        Qt::WindowMinimizeButtonHint |
        Qt::WindowStaysOnTopHint);
    this->setMinimumWidth(650);
    this->setFixedHeight(translate_box_height);
    this->setFocusPolicy(Qt::StrongFocus);
    //this->youdaoTranslate("are you ok");
    connect(this,
            SIGNAL(translateResult(std::vector<QString>)),
            this,
            SLOT(displayResult(std::vector<QString>)));
    resgisterHotKey();
}

void Translate::youdaoTranslate(const QString& source) {
    QString baseUrl = QString("http://openapi.youdao.com/api");

    int salt = 2;

    QByteArray data_array;
    data_array.append("q=");
    data_array.append(source.toUtf8().toPercentEncoding());
    data_array.append("&from=");
    data_array.append("auto");
    data_array.append("&to=");
    data_array.append("auto");
    data_array.append("&appKey=");
    data_array.append(APP_KEY);
    data_array.append("&salt=");
    data_array.append(QString::number(salt));
    data_array.append("&sign=");
    data_array.append(getYoudaoSign(source, salt));

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(baseUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply* reply_p = manager->post(request, data_array);
    connect(reply_p,
            &QNetworkReply::finished,
            this,
            [=]()
            {
                if (reply_p->error() != QNetworkReply::NoError) {
                    qDebug() << "Error String : " << reply_p->errorString();
                } else {
                    QByteArray reply_data = reply_p->readAll();

                    qDebug() << reply_data;

                    QJsonParseError error;
                    QJsonDocument json_document = QJsonDocument::fromJson(reply_data, &error);
                    if (error.error == QJsonParseError::NoError) {
                        if (!(json_document.isNull() || json_document.isEmpty()) && json_document.
                            isObject()) {
                            QVariantMap data = json_document.toVariant().toMap();
                            //                    qDebug() << data;
                            int errorcode = data[QLatin1String("errorCode")].toInt();

                            if (0 == errorcode) {
                                std::vector<QString> result;
                                QVariantList detailList = data[QLatin1String("translation")].
                                    toList();
                                QString str = detailList.first().toString();
                                result.push_back(str);

                                auto basicMap = data[QLatin1String("basic")].toMap();
                                auto detailTranslations = basicMap[QLatin1String("explains")].
                                    toList();
                                for (auto i : detailTranslations) {
                                    result.push_back(i.toString());
                                }
                                emit translateResult(result);
                            }
                        }
                    } else {
                        qDebug() << "Error String : " << error.errorString();
                    }
                }

                reply_p->deleteLater();
            });
}

QByteArray Translate::getYoudaoSign(const QString& source, int salt) {
    QByteArray sign;

    QString str = APP_KEY + source + QString::number(salt) + APP_SECRET;

    sign = QCryptographicHash::hash(str.toUtf8(), QCryptographicHash::Md5).toHex().toUpper();
    return sign;
}

void Translate::resgisterHotKey() {
#ifdef LON_WINDOWS
    RegisterHotKey((HWND)winId(), ACTIVE_WINDOW, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 'M');
#endif
}

void Translate::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Cancel:
            hideWindow();
            break;
        case Qt::Key_Enter:
            doTranSlate();
            break;
        default:
            break;
    }
}

void Translate::focusOutEvent(QFocusEvent* event) {
    Q_UNUSED(event);

    hideWindow();
}

bool Translate::eventFilter(QObject* watched, QEvent* event) {
    Q_UNUSED(watched);

    if (event->type() == QEvent::KeyPress) {
        auto key_event = static_cast<QKeyEvent*>(event);
        switch (key_event->key()) {
            case Qt::Key_Escape:
            case Qt::Key_Cancel:
                hideWindow();
                break;
            case Qt::Key_Return:
            case Qt::Key_Enter:
                doTranSlate();
                break;
            default:
                break;
        }
    } else if (event->type() == QEvent::FocusOut) {
        hideWindow();
    }
    return false;
}

bool Translate::nativeEvent(const QByteArray& eventType, void* message, long* result) {
    Q_UNUSED(result);

    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG*>(message);
        if (msg->message == WM_HOTKEY) {
            switch (msg->wParam) {
                case ACTIVE_WINDOW:
                    activeWindowListener();
                    break;
                default:
                    assert(0 && "unhandled message from windows");
            }
        }
    }
    return false;
}

void Translate::hideWindow() {
    this->window()->setVisible(false);
    clearResultDisplaying();
}

void Translate::activeWindowListener() {
    if (this->isVisible())
        hideWindow();
    else {
        this->show();
        this->activateWindow();
        line_edit_p_->setFocus();
    }
}

void Translate::doTranSlate() {
    clearResultDisplaying();
    auto source = line_edit_p_->text();
    if (!source.isEmpty())
        youdaoTranslate(source);
}

void Translate::clearResultDisplaying() {
    while (vertical_layout_p_->count() > 1) {
        delete vertical_layout_p_->takeAt(1)->widget();
    }
    this->setFixedHeight(translate_box_height);
}

void Translate::displayResult(std::vector<QString> result) {
    QFont font;
    font.setFamily(QString::fromUtf8("Microsoft YaHei"));
    font.setPointSize(16);
    result.erase(std::unique(result.begin(), result.end()), result.end());
    for (auto i : result) {
        QLineEdit* line_edit = new QLineEdit(this);
        line_edit->setReadOnly(true);
        line_edit->setText(i);
        line_edit->setFont(font);
        line_edit->setFixedHeight(translate_box_height);
        vertical_layout_p_->addWidget(line_edit);
        this->setFixedHeight(this->height() + translate_box_height);
    }
}
