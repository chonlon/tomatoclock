#ifndef LON_BUTTON
#define LON_BUTTON

#include <QPushButton>
#include <QtGui>
#include <memory>
#ifdef DEBUG
#include <vector>
/// <summary>
/// --调试函数--
/// 返回对应目录下所有文件文件名
/// </summary>
/// <param name: "dir"> 需要查看的目录 </param>
/// <returns> 目录下的所有文件的文件名数组 </returns>
static std::vector<QString> GetFileList(QString dir) {
    std::vector<QString> filePath;
    QDir                 dirPath(dir);
    QList<QFileInfo>     file(dirPath.entryInfoList());
    QString              name = "";

    for (auto it = file.begin(); it != file.end(); it++) {
        name = dir + "/" + it->fileName();
        if ((*it).isFile()) {
            filePath.push_back(name);
        }
    }
    return filePath;
}
#endif // DEBUG

namespace lon {
/// <summary>
/// 默认的不是flat的,(因为如果图标设置失败, 而按钮已经时flat的会很尴尬)
/// 所以添加icon后还是会有边框和背景, 如果不想要, 使用button->setFlat(true)即可.
/// </summary>
class Button : public QPushButton {
    Q_OBJECT
  private:
    std::shared_ptr<QIcon> normal_icon_;
    std::shared_ptr<QIcon> focus_icon_;
    std::shared_ptr<QIcon> pressed_icon_;

    double scaling_factor_;

  protected:
    /// <summary>
    /// 鼠标进入按钮事件, 改变图标为focus.
    /// 设置失败只在调试时提示, 不影响程序运行.
    /// </summary>
    virtual void enterEvent(QEvent *event) {
        Q_UNUSED(event)

        if (this->isEnabled() && focus_icon_) {
            this->setIcon(*focus_icon_);
            qDebug() << focus_icon_->data_ptr();
        } else {
            qDebug() << "button is not enabled or icon is not exits";
        }
    }

    /// <summary>
    /// 鼠标进入按钮事件, 改变图标为normal.
    /// 设置失败只在调试时提示, 不影响程序运行.
    /// </summary>
    virtual void leaveEvent(QEvent *event) {
        Q_UNUSED(event)

        if (this->isEnabled() && normal_icon_) {
            this->setIcon(*normal_icon_);
        } else {
            qDebug() << "button is not enabled or icon is not exits";
        }
    }

    /// <summary>
    /// 鼠标按下按钮事件, 改变图标为pressed.
    /// 设置失败只在调试时提示, 不影响程序运行.
    /// </summary>
    virtual void mousePressEvent(QMouseEvent *event) {
        if (this->isEnabled() && pressed_icon_) {
            this->setIcon(*pressed_icon_);
        } else {
            qDebug() << "button is not enabled or icon is not exits";
        }
        QPushButton::mousePressEvent(event);
    }

    /// <summary>
    /// 鼠标松开按钮事件, 改变图标为focus.
    /// 设置失败只在调试时提示, 不影响程序运行.
    /// </summary>
    virtual void mouseReleaseEvent(QMouseEvent *event) {
        if (this->isEnabled() && focus_icon_) {
            this->setIcon(*focus_icon_);
        } else {
            qDebug() << "button is not enabled or icon is not exits";
        }
        QPushButton::mouseReleaseEvent(event);
    }

    virtual void setIcon(const QIcon &icon) {
        QPushButton::setIcon(icon);
        this->setIconSize(QSize(this->width() * scaling_factor_,
                                this->height() * scaling_factor_));
    }

    virtual void resizeEvent(QResizeEvent *event) {
        QPushButton::resizeEvent(event);
        this->setIconSize(QSize(this->width() * scaling_factor_,
                                this->height() * scaling_factor_));
    }

  public:
    /// <summary>
    /// 设置默认按钮图标.
    /// 前面注释的部分是用于查看当前icon的图片是否放置于正确路径
    /// 如果发现设置图标失败, 可以试试取消注释, 查看当前路径是什么
    /// 以及是否存在icon文件
    /// </summary>
    /// <param name: parent> 用于设置当前Button的parent </param>
    Button(QWidget *parent = nullptr)
        : QPushButton(parent)
        , scaling_factor_(0.8) {
        normal_icon_.reset(new QIcon("normal.png"));
        focus_icon_.reset(new QIcon("focus.png"));
        pressed_icon_.reset(new QIcon("pressed.png"));
        this->setIcon(*normal_icon_);
    }

    /// <summary>
    /// 以自定义的图标设置按钮,
    /// 使用这个方式会接管三个icon的指针指向变量的所有权.
    /// </summary>
    /// <param name = "pnormal_icon"> </param>
    Button(QIcon *pnormal_icon, QIcon *pfocus_icon, QIcon *ppressed_icon,
           QWidget *parent = nullptr)
        : QPushButton(parent)
        , scaling_factor_(0.8) {
        if (pnormal_icon == nullptr) {
            normal_icon_.reset(new QIcon("./normal.png"));
        } else {
            normal_icon_.reset(pnormal_icon);
        }

        if (pfocus_icon == nullptr) {
            focus_icon_.reset(new QIcon("./focus.png"));
        } else {
            focus_icon_.reset(pfocus_icon);
        }

        if (ppressed_icon == nullptr) {
            pressed_icon_.reset(new QIcon("./pressed.png"));
        } else {
            pressed_icon_.reset(ppressed_icon);
        }
        this->setIcon(*normal_icon_);
    }

    /// <summary>
    /// 以自定义的图标设置按钮,
    /// 使用智能指针管理icon内存.
    /// </summary>
    Button(const std::shared_ptr<QIcon> &normal_icon,
           const std::shared_ptr<QIcon> &focus_icon,
           const std::shared_ptr<QIcon> &pressed_icon,
           QWidget *                     parent = nullptr)
        : QPushButton(parent)
        , scaling_factor_(0.8) {
        normal_icon_  = normal_icon;
        focus_icon_   = focus_icon;
        pressed_icon_ = pressed_icon;
        this->setIcon(*normal_icon_);
    }

    /// <summary>
    /// 设置button中的图标缩放比例
    /// </summary>
    /// <param name="factor">缩放比例, 范围 0 - 1</param>
    void setScalingFactor(double factor) {
        scaling_factor_ = factor;
        this->setIconSize(QSize(this->width() * scaling_factor_,
                                this->height() * scaling_factor_));
    }

    /// <summary> 设置normal图标, 接管指针所指内存管理权 </summary>
    virtual void setNormal(QIcon *normal) {
        if (normal == nullptr) return;
        normal_icon_.reset(normal);

        this->setIcon(*normal_icon_);
    }

    /// <summary> 设置normal图标, 以智能指针管理内存 </summary>
    virtual void setNormal(const std::shared_ptr<QIcon> &normal) {
        normal_icon_ = normal;

        this->setIcon(*normal_icon_);
    }

    /// <summary> 设置focus图标, 接管指针所指内存管理权 </summary>
    virtual void setFocus(QIcon *focus) {
        if (focus == nullptr) return;
        focus_icon_.reset(focus);
    }

    /// <summary> 设置focus图标, 以智能指针管理内存 </summary>
    virtual void setFocus(const std::shared_ptr<QIcon> &focus) {
        focus_icon_ = focus;
    }

    /// <summary> 设置pressed图标, 接管指针所指内存管理权 </summary>
    virtual void setPressed(QIcon *pressed) {
        if (pressed == nullptr) return;
        pressed_icon_.reset(pressed);
    }

    /// <summary> 设置pressed图标, 以智能指针管理内存 </summary>
    virtual void setPressed(const std::shared_ptr<QIcon> &pressed) {
        pressed_icon_ = pressed;
    }

    virtual ~Button() {
        normal_icon_  = nullptr;
        focus_icon_   = nullptr;
        pressed_icon_ = nullptr;
    }
};
} // namespace lon
#endif