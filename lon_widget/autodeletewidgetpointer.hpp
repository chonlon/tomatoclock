#ifndef AUTODELETEWIDGETPOINTER_H
#define AUTODELETEWIDGETPOINTER_H

#include <thread>
class QWidget;
static void deleteAfterMs(unsigned int duration, QWidget **w_pointer) {
    if(*w_pointer == nullptr) return;
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    delete  (*w_pointer);
    *w_pointer = nullptr;
}


namespace lon {
/// <summary>
/// class holds widget pointer and auto delete the widget after duration.
/// the ownship of widget pointer will passed to this class.
/// </summary>
class AutoDeleteWidgetPointer {
private:
    QWidget* widget_p_;
    // copy action and default constructor are not allowed.
    AutoDeleteWidgetPointer(){}
    AutoDeleteWidgetPointer(const AutoDeleteWidgetPointer&){}
    void operator=(const AutoDeleteWidgetPointer&){}
 public:

    AutoDeleteWidgetPointer(unsigned int widget_duration, QWidget* widget) {
        widget_p_ = widget;
        // new a thread to delete pointer after duration, and will not block this thread.
        std::thread t(deleteAfterMs, widget_duration, &widget_p_);
        t.detach();
    }


    bool isNull() { return widget_p_ == nullptr; }
};
}

#endif // AUTODELETEWIDGETPOINTER_H
