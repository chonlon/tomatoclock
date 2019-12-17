set(LonWidgetSrc
	autodeletewidgetpointer.hpp
	button.hpp
	listwidget.hpp
	menu.hpp
	messagebox.hpp
	titlebar.hpp
	widget.hpp
	lon_widget.qrc
)

add_library(LonWidgetLib STATIC ${LonWidgetSrc})
target_link_libraries(LonWidgetLib Qt5::Widgets Qt5::Gui Qt5::Core)