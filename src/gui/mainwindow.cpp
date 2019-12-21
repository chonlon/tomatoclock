#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    layout_ = new QHBoxLayout(this);
    // temp_   = new temp(this);
    // temp_->show();

    this->resize(1000, 1000);

    const float Pi = 3.14159f;

    // 定义一个 item
    QGraphicsPathItem* pItem = new QGraphicsPathItem();

    // 绘制星星
    QPainterPath starPath;
    starPath.moveTo(90, 50);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(50 + 40 * std::cos(0.8 * i * Pi),
                        50 + 40 * std::sin(0.8 * i * Pi));
    }
    starPath.closeSubpath();
    pItem->setPath(starPath);

    // 设置画笔、画刷
    QPen pen = pItem->pen();
    pen.setWidth(2);
    pen.setColor(Qt::white);
    pItem->setPen(pen);
    pItem->setBrush(QBrush(QColor(0, 160, 230)));

    // 将 item 添加至场景中
    QGraphicsScene* pScene = new QGraphicsScene();
    pScene->addItem(pItem);

    // 为视图设置场景
    QGraphicsView* pView = new QGraphicsView();
    pView->setScene(pScene);
    pView->setStyleSheet("border:none; background:transparent;");

    painter = new QPainter();

    pView->show();
}

MainWindow::~MainWindow() {
}
