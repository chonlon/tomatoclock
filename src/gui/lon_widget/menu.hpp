#ifndef MENU_H
#define MENU_H

#include <QMenu>

namespace lon {
class Menu : public QMenu {
Q_OBJECT
public:
    explicit Menu(QWidget* parent = nullptr) { init(); }
    explicit Menu(const QString& title) { init(); }

    void init() {
        setMenu(QColor("#46e6b7"));

        // 必须设置popup,
        // 因为QMenuPrivate::activateAction中使用QApplication::activePopupWidget()函数
        this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
        this->setAttribute(Qt::WA_TranslucentBackground);
        // 以objectname 区分Qt内置菜单和CCustomMenu
        this->setObjectName("CustomMenu");
    }

protected:
private:
    void setMenu(QColor hoverColor) {
        /*Qmenu Style Sheets*/
        QString qss;
        QFont f("consolas", 12, QFont::Normal);
        //    qss = "QMenu{ background-color: rgb(255, 255, 255); border: 1px
        //    solid rgb(125, 125, 125); border-radius: 6px; }"
        //          "QMenu::item { background-color: transparent; padding:3px
        //          20px;/*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/
        //          margin:5px 10px;/*设置菜单项的外边距: 长(height) 宽(width)*/
        //          border-bottom:1px solid #DBDBDB;/*为菜单项之间添加横线间隔*/
        //          }" "QMenu::item:selected { background-color: "+
        //          hoverColor.name()
        //          +";/*这一句是设置菜单项鼠标经过选中的样式*/ }";
        //    menu->setStyleSheet(qss);
        const QString MenuStyle =
            " \
                QMenu{ padding:5px; border:none; background:rgba(255, 255, 255, 210); border-radius:4px;} \
                QMenu::icon{ margin-left:10px;} \
                QMenu::item{ color:rab(0, 0, 0); padding:6px 30px 6px 30px; border:1px solid transparent;} \
                QMenu::item:disabled{ color:#555555;} \
                QMenu::item:selected{ color:white; background:rgba(0, 0, 0, 200);} \
                QMenu::separator{ height:1px; background:#BBBBBB; margin-top:5px; margin-bottom:5px;}";
        this->setStyleSheet(MenuStyle);
        this->setFont(f);
    }

signals:

public slots:
};
} // namespace lon

#endif // MENU_H
