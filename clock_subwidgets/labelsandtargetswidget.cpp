#include "labelsandtargetswidget.h"
#include "clock_database/clocksql.hpp"
#include "clock_subwidgets/addlabelwidget.h"
#include "clock_subwidgets/addtargetwidget.h"
#include "clock_subwidgets/targetwidget.h"
#include "lon_widget/button.hpp"
#include "lon_widget/listwidget.hpp"

#include <iostream>
#include <list>

static const unsigned int duration            = 600000;
static const unsigned int label_widget_height = 110;
static const int          button_width_height = 50;

lon::LabelsAndTargetsWidget::LabelsAndTargetsWidget(
    std::shared_ptr<lon::tomato_clock::LastWeekData> week_data,
    std::shared_ptr<lon::tomato_clock::LastMonthData> month_data,
    QWidget *                                         parent)
    : QWidget(parent)
    , sql_(lon::ClockSql::Get())
    , current_cloumn(0)
    , current_row(0)
    , last_week_data_p_(week_data)
    , last_month_data_p_(month_data) {
    main_layout_p_        = new QVBoxLayout(this);
    labels_and_targets_p_ = new std::list<std::pair<QString, QString>>(
        sql_->getAllTargetsAndLabels());
    addlabelwidget_p_  = nullptr;
    addtargetwidget_p_ = nullptr;

    // labels ..
    initLabelsLayout();
    // targets..
    initTargetsLayout();
    // ""means all target.
    initTargets("", true);

    initConnect();
    // set this widget..
    main_layout_p_->addLayout(labels_main_layout_p_);
    main_layout_p_->addLayout(target_main_layout_p_);
    this->setLayout(main_layout_p_);
}

void lon::LabelsAndTargetsWidget::setLastWeekData(
    std::shared_ptr<lon::tomato_clock::LastWeekData> ptr) {
    last_week_data_p_ = ptr;
}

void lon::LabelsAndTargetsWidget::setLastMonthData(
    std::shared_ptr<lon::tomato_clock::LastMonthData> ptr) {
    last_month_data_p_ = ptr;
}

void lon::LabelsAndTargetsWidget::initLabelsLayout() {
    labels_widget_p_           = new QWidget(this);
    labels_layout_p_           = new QGridLayout(labels_widget_p_);
    labels_main_layout_p_      = new QHBoxLayout(labels_widget_p_);
    add_label_button_layout_p_ = new QVBoxLayout(labels_widget_p_);

    add_label_button_p_ = new lon::Button(this);
    add_label_button_p_->setFlat(true);
    add_label_button_p_->setNormal(
        new QIcon(":/icon/Icons/add_label_custom.png"));
    add_label_button_p_->setFocus(
        new QIcon(":/icon/Icons/add_label_focus.png"));
    add_label_button_p_->setPressed(
        new QIcon(":/icon/Icons/add_label_focus.png"));
    add_label_button_p_->setStyleSheet("border:none");
    add_label_button_p_->setScalingFactor(0.9);

    labels_widget_p_->setFixedHeight(label_widget_height);
    add_label_button_p_->setFixedSize(button_width_height, button_width_height);
    add_label_button_p_->setToolTip(QString::fromLocal8Bit("添加标签"));

    // 关于layout的addSapcerItem, 文档里面没有写明会获得item指针的所有权,
    // 但事实上是获得了的(写在addItem里面了...).
    // 所以同一个spacer_item不能添加两次.
    // 而且, 在这个类的析构函数中不需要考虑释放spacer_item的内存.
    unsigned int height    = (label_widget_height - button_width_height) / 2;
    label_widget_spacer_p_ = new QSpacerItem(
        height, height, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *item_copy = new QSpacerItem(*label_widget_spacer_p_);

    labels_widget_p_->setLayout(labels_layout_p_);
    labels_layout_p_->setContentsMargins(0, 0, 0, 0);

    add_label_button_layout_p_->addSpacerItem(label_widget_spacer_p_);
    add_label_button_layout_p_->addWidget(add_label_button_p_);
    add_label_button_layout_p_->addSpacerItem(item_copy);

    labels_main_layout_p_->addWidget(labels_widget_p_);
    labels_main_layout_p_->addLayout(add_label_button_layout_p_);

    // labels_main_layout_p_->setAlignment(add_label_button_layout_p_,
    //                                         Qt::AlignRight);

    std::list<QString> labels_name(sql_->getAllLabels());
    labels_name.push_front(QString::fromLocal8Bit("所有"));
    uint8_t count = 1;
    for (auto i : labels_name) {
        lon::Button *button = new lon::Button(labels_widget_p_);
        if (count == 1) {
            all_button_ = button;
            count       = 2;
        }
        addLabelButton(button, i);
    }
}

void lon::LabelsAndTargetsWidget::initTargetsLayout() {
    target_main_layout_p_   = new QHBoxLayout(this);
    target_button_layout_p_ = new QVBoxLayout(this);
    targets_list_widget_p_  = new lon::ListWidget(this);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QColor(255, 255, 255, 30)));
    targets_list_widget_p_->setPalette(palette);

    button_map_[ all_button_ ] =
        new lon::AutoDeleteWidgetPointer(duration, targets_list_widget_p_);
    current_widget_pointer_ = button_map_[ all_button_ ];
    button_map_[ all_button_ ]->setShouldDelete(false);

    target_main_layout_p_->addWidget(targets_list_widget_p_);

    target_button_spacer_p_ =
        new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    add_target_button_p_ = new lon::Button(this);
    history_button_p_    = new lon::Button(this);
    setting_button_p_    = new lon::Button(this);

    add_target_button_p_->setFlat(true);
    history_button_p_->setFlat(true);
    add_target_button_p_->setNormal(
        new QIcon(":/icon/Icons/add_target_custom.png"));
    add_target_button_p_->setFocus(
        new QIcon(":/icon/Icons/add_target_focus.png"));
    add_target_button_p_->setPressed(
        new QIcon(":/icon/Icons/add_target_pressed.png"));
    add_target_button_p_->setStyleSheet("border:none");
    history_button_p_->setNormal(new QIcon(":/icon/Icons/history_custom.png"));
    history_button_p_->setFocus(new QIcon(":/icon/Icons/history_focus.png"));
    history_button_p_->setPressed(
        new QIcon(":/icon/Icons/history_pressed.png"));
    history_button_p_->setStyleSheet("border:none");
    add_target_button_p_->setScalingFactor(0.9);
    history_button_p_->setScalingFactor(0.9);

    add_target_button_p_->setFixedSize(button_width_height,
                                       button_width_height);
    add_target_button_p_->setToolTip(QString::fromLocal8Bit("添加目标"));
    history_button_p_->setFixedSize(button_width_height, button_width_height);
    history_button_p_->setToolTip(QString::fromLocal8Bit("查看历史番茄"));
    setting_button_p_->setFixedSize(button_width_height, button_width_height);
    setting_button_p_->setToolTip(QString::fromLocal8Bit("设置"));
    setting_button_p_->setFlat(true);
    setting_button_p_->setNormal(new QIcon(":/icon/Icons/setting_normal.png"));
    setting_button_p_->setFocus(new QIcon(":/icon/Icons/setting_focus.png"));
    setting_button_p_->setPressed(
        new QIcon(":/icon/Icons/setting_pressed.png"));
    setting_button_p_->setStyleSheet("border:none");

    target_button_layout_p_->addWidget(add_target_button_p_);
    target_button_layout_p_->addWidget(history_button_p_);
    target_button_layout_p_->addSpacerItem(target_button_spacer_p_);
    target_button_layout_p_->addWidget(setting_button_p_);

    target_main_layout_p_->addLayout(target_button_layout_p_, Qt::AlignRight);
}

void lon::LabelsAndTargetsWidget::addTargetWidget(QString labelname,
                                                  QString targetname,
                                                  int     index) {
    lon::TargetWidget *target_widget =
        new lon::TargetWidget(labelname, targetname, this);
    target_widget->setLastWeekData(last_week_data_p_);
    target_widget->setLastMonthData(last_month_data_p_);
    if (index == -1)
        targets_list_widget_p_->addWidget(target_widget);
    else
        targets_list_widget_p_->insertWidget(index, target_widget);
    connect(target_widget, SIGNAL(startButtonClicked(QString, QString)), this,
            SIGNAL(startClock(QString, QString)));
    connect(target_widget, SIGNAL(targetFinished(const QString&)), this,
            SLOT(targetFinished(const QString &)));
}

void lon::LabelsAndTargetsWidget::addLabelButton(lon::Button *  button,
                                                 const QString &text) {
    const uint8_t row_width = 8;

    button->setFixedSize(60, 30);
    button->setText(text);
    button->setToolTip(text);
    labels_layout_p_->addWidget(button, current_row, current_cloumn);
    if (++current_cloumn == row_width) {
        current_cloumn = 0;
        ++current_row;
    }
    button_map_[ button ] = nullptr;
    button->setStyleSheet(
        "QPushButton{border-image: url(:/icon/Icons/label_normal.png);}"
        "QPushButton:hover{border-image: url(:/icon/Icons/label_focus.png);}"
        "QPushButton:pressed{border-image: "
        "url(:/icon/Icons/label_pressed.png);}"
        "QPushButton{text-align : left;}");
    connect(button, SIGNAL(clicked()), this, SLOT(onLabelButtonClicked()));
}

void lon::LabelsAndTargetsWidget::saveLabelToSql(const QString &label_name) {
    sql_->addLabel(label_name);
}

void lon::LabelsAndTargetsWidget::saveTargetToSql(const QString &label_name,
                                                  const QString &target_name) {
    sql_->addTarget(label_name, target_name);
}

void lon::LabelsAndTargetsWidget::initTargets(QString label_name,
                                              bool    getAllTargets) {
    if (getAllTargets) {
        for (auto i : (*labels_and_targets_p_)) {
            addTargetWidget(i.first, i.second);
        }
    } else {
        // 查找所有label为label_name的target
        auto iter = labels_and_targets_p_->begin();
        // 遍历到第一个label名字等于label_name的地方.
        for (; iter != labels_and_targets_p_->end(); ++iter) {
            if (iter->first == label_name) break;
        }

        for (;
             iter != labels_and_targets_p_->end() && iter->first == label_name;
             ++iter) {
            addTargetWidget(label_name, iter->second);
        }
    }

    if (targets_list_widget_p_->count() == 0 && label_name.size()) {
        lon::Button *delete_label_button =
            new lon::Button(targets_list_widget_p_);
        delete_label_button->setFixedSize(100, 50);
        delete_label_button->setText(QString("%1%2")
                                         .arg(QString::fromLocal8Bit("删除 "))
                                         .arg(label_name));
        connect(delete_label_button, SIGNAL(clicked()), this,
                SLOT(deleteLabel()));
    }
}

void lon::LabelsAndTargetsWidget::initConnect() {
    connect(add_label_button_p_, SIGNAL(clicked()), this, SLOT(addLabel()));
    connect(add_target_button_p_, SIGNAL(clicked()), this, SLOT(addTarget()));
    connect(setting_button_p_, SIGNAL(clicked()), this,
            SIGNAL(changeSetting()));
    connect(history_button_p_, SIGNAL(clicked()), this, SIGNAL(showChart()));
}

void lon::LabelsAndTargetsWidget::deleteLabel() {
    QPushButton *button     = qobject_cast<QPushButton *>(sender());
    auto         i          = button->text();
    auto         label_name = i.right(i.length() - 3);
    sql_->deleteLabel(label_name);
    emit redrawWidget();
}

void lon::LabelsAndTargetsWidget::closeAddLabelWidget() {
    if (addlabelwidget_p_) {
        addlabelwidget_p_->window()->close();
        delete addlabelwidget_p_;
        addlabelwidget_p_ = nullptr;
    }
}

void lon::LabelsAndTargetsWidget::closeAddTargetWidget() {
    if (addtargetwidget_p_) {
        addtargetwidget_p_->window()->close();
        delete addtargetwidget_p_;
        addtargetwidget_p_ = nullptr;
    }
}

void lon::LabelsAndTargetsWidget::addTarget() {
    auto labels             = sql_->getAllLabels();
    auto addtargetwidget_p_ = new lon::AddTargetWidget(labels);
    addtargetwidget_p_->show();
    connect(addtargetwidget_p_, SIGNAL(targetAdded(QString, QString)), this,
            SLOT(targetAdded(QString, QString)));
    connect(addtargetwidget_p_, SIGNAL(closeButtonClicked()), this,
            SLOT(closeAddTargetWidget()));
    connect(addtargetwidget_p_, SIGNAL(cancelButtonClicked()), this,
            SLOT(closeAddTargetWidget()));
}

void lon::LabelsAndTargetsWidget::addLabel() {
    auto labels       = sql_->getAllLabels();
    addlabelwidget_p_ = new lon::AddLabelWidget(labels);
    addlabelwidget_p_->show();
    connect(addlabelwidget_p_, SIGNAL(labelAdded(QString)), this,
            SLOT(labelAdded(QString)));
    connect(addlabelwidget_p_, SIGNAL(cancelButtonClicked()), this,
            SLOT(closeAddLabelWidget()));
    connect(addlabelwidget_p_, SIGNAL(closeButtonClicked()), this,
            SLOT(closeAddLabelWidget()));
}

void lon::LabelsAndTargetsWidget::labelAdded(QString text) {
    lon::Button *button = new lon::Button(this);
    addLabelButton(button, text);
    saveLabelToSql(text);
    closeAddLabelWidget();
}

void lon::LabelsAndTargetsWidget::targetAdded(QString label, QString target) {
    addTargetWidget(label, target, 0);
    saveTargetToSql(label, target);
    closeAddTargetWidget();
	emit redrawWidget();
}

void lon::LabelsAndTargetsWidget::targetFinished(const QString &target_name) {
	sql_->deleteTarget(target_name);
	emit redrawWidget();
}

void lon::LabelsAndTargetsWidget::onLabelButtonClicked() {
    lon::Button *button = qobject_cast<lon::Button *>(sender());
    // 如果点击的现在的widget对应的button
    // 这么写应该不会有多少影响, 下面执行很快, 刚好使计时少10ms的概率很低,
    // 而且发生了影响不大.
    current_widget_pointer_->getWidgetPointer()->setVisible(false);
    current_widget_pointer_->setShouldDelete(true);

    auto iter = button_map_.find(button);
    if (iter == button_map_.end()) {
        button_map_[ button ] = nullptr;
        return;
    }
    if (iter->second == nullptr || iter->second->isNull()) {
        if (iter->second && iter->second->isNull()) {
            delete iter->second;
            iter->second = nullptr;
        }
        // repalce current target list widget with targets belong the clicked
        // label.
        target_main_layout_p_->removeWidget(targets_list_widget_p_);
        targets_list_widget_p_ = new lon::ListWidget(this);
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(255, 255, 255, 30));
        targets_list_widget_p_->setPalette(palette);
        iter->second =
            new lon::AutoDeleteWidgetPointer(duration, targets_list_widget_p_);
        current_widget_pointer_ = iter->second;
        initTargets(button->text());
        target_main_layout_p_->insertWidget(0, targets_list_widget_p_);
    } else {
        target_main_layout_p_->removeWidget(targets_list_widget_p_);
        targets_list_widget_p_ =
            dynamic_cast<lon::ListWidget *>(iter->second->getWidgetPointer());
        target_main_layout_p_->insertWidget(0, targets_list_widget_p_);
        current_widget_pointer_ = iter->second;
    }
    current_widget_pointer_->setShouldDelete(false);
    current_widget_pointer_->getWidgetPointer()->setVisible(true);
}

// void lon::LabelsAndTargetsWidget::startClock(const QString &label_name,const
// QString &target_name)
//{
//	qDebug() << "-------------" << label_name << "=======" << target_name;
//}