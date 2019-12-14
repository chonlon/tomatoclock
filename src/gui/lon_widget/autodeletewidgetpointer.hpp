#ifndef AUTODELETEWIDGETPOINTER_H
#define AUTODELETEWIDGETPOINTER_H

#include <mutex>
#include <thread>
class QWidget;

/// <summary>
/// 在duration生命周期后, 删除*w_pointer所指内容并将*w_pointer置为nullptr
/// </summary>
static void deleteAfterMs(unsigned int duration,
                          QWidget** w_pointer,
                          std::mutex& mutex,
                          bool& should_delete) {
    if (*w_pointer == nullptr)
        return;
    unsigned int left = duration;
    while (left > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
            std::lock_guard<std::mutex> lm(mutex);
            if (should_delete)
                left -= 10;
        }
    }
    if (left == 0) {
        std::lock_guard<std::mutex> lm(mutex);
        delete (*w_pointer);
    }
    *w_pointer = nullptr;
}

namespace lon {
/// <summary>
/// class holds widget pointer and auto delete the widget after duration.
/// the ownship of widget pointer will passed to this class.
/// </summary>
class AutoDeleteWidgetPointer {
private:
    std::mutex pointer_mutex_;
    QWidget* widget_p_;
    bool should_delete_;
    // copy action and default constructor are not allowed.
    AutoDeleteWidgetPointer() {
    }

    AutoDeleteWidgetPointer(const AutoDeleteWidgetPointer&) {
    }

    void operator=(const AutoDeleteWidgetPointer&) {
    }

public:
    AutoDeleteWidgetPointer(unsigned int widget_duration, QWidget* widget) {
        widget_p_ = widget;
        should_delete_ = false;
        // new a thread to delete pointer after duration, and will not block
        // this thread.
        std::thread t(deleteAfterMs,
                      widget_duration,
                      &widget_p_,
                      std::ref(pointer_mutex_),
                      std::ref(should_delete_));
        t.detach();
    }

    /// <summary>
    /// 所管理的widget指针是否为空.
    /// </summary>
    bool isNull() {
        std::lock_guard<std::mutex> lm(pointer_mutex_);
        return widget_p_ == nullptr;
    }

    /// <summary>
    /// 当前指针是否该被删除, iff should_delete == true, 会持续缩减所持有的widget指针的生命周期.
    /// </summary>
    void setShouldDelete(bool should_delete) {
        std::lock_guard<std::mutex> lm(pointer_mutex_);
        should_delete_ = should_delete;
    }

    /// <summary>
    /// 获取所管理的widget的指针.
    /// </summary>
    QWidget* getWidgetPointer() {
        std::lock_guard<std::mutex> lm(pointer_mutex_);
        return widget_p_;
    }
};
} // namespace lon

#endif // AUTODELETEWIDGETPOINTER_H
