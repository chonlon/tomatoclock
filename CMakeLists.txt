#|---------------------------------------------------------------------------------------|#
#|                      较新版本cmake qt项目写法                                            |#
#|---------------------------------------------------------------------------------------|#
cmake_minimum_required(VERSION 3.0.2)
project(tomatoclock)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Gui Network PrintSupport Widgets Sql Charts REQUIRED)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_CXX_STANDARD 11)

if (WIN32)
	get_filename_component(QT_BINARY_DIR "${QT_MOC_EXECUTABLE}" PATH)
	set(QT_PLUGINS_DIR "${QT_BINARY_DIR}/../plugins")

	function(COPY_QT_BINARIES IS_DEBUG IS_APP)
		set(SUFFIX "")
		if (IS_DEBUG)
			set(SUFFIX "d")
		endif()

		set(CONFIGURATION "Release")
		if (IS_DEBUG)
			set(CONFIGURATION "Debug")
		endif()

		if(CMAKE_CL_64)
			set(BITS "64")
		else()
			set(BITS "32")
		endif()

		set(TARGET "test")
		if (IS_APP)
			set(TARGET "app")

			file(GLOB MY_PUBLIC_HEADERS
				"${CMAKE_SOURCE_DIR}/setup/dynamic_libraries/win${BITS}/app/${CONFIGURATION}/*"
			)
			file(COPY ${MY_PUBLIC_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/")

		endif()

		configure_file("${QT_BINARY_DIR}/Qt5Core${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/Qt5Core${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_BINARY_DIR}/Qt5Gui${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/Qt5Gui${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_BINARY_DIR}/Qt5Network${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/Qt5Network${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_BINARY_DIR}/Qt5Svg${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/Qt5Svg${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_BINARY_DIR}/Qt5Widgets${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/Qt5Widgets${SUFFIX}.dll" COPYONLY)
		#configure_file("${QT_BINARY_DIR}/Qt5WinExtras${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/Qt5WinExtras${SUFFIX}.dll" COPYONLY)

		configure_file("${QT_PLUGINS_DIR}/platforms/qwindows${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/platforms/qwindows${SUFFIX}.dll" COPYONLY)

		configure_file("${QT_PLUGINS_DIR}/styles/qwindowsvistastyle${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/styles/qwindowsvistastyle${SUFFIX}.dll" COPYONLY)

		configure_file("${QT_PLUGINS_DIR}/imageformats/qgif${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/imageformats/qgif${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_PLUGINS_DIR}/imageformats/qicns${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/imageformats/qicns${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_PLUGINS_DIR}/imageformats/qico${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/imageformats/qico${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_PLUGINS_DIR}/imageformats/qjpeg${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/imageformats/qjpeg${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_PLUGINS_DIR}/imageformats/qsvg${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/imageformats/qsvg${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_PLUGINS_DIR}/imageformats/qtga${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/imageformats/qtga${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_PLUGINS_DIR}/imageformats/qtiff${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/imageformats/qtiff${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_PLUGINS_DIR}/imageformats/qwbmp${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/imageformats/qwbmp${SUFFIX}.dll" COPYONLY)
		configure_file("${QT_PLUGINS_DIR}/imageformats/qwebp${SUFFIX}.dll" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}/imageformats/qwebp${SUFFIX}.dll" COPYONLY)
	endfunction(COPY_QT_BINARIES)

	COPY_QT_BINARIES(True True)
	COPY_QT_BINARIES(True False)
	COPY_QT_BINARIES(False True)
	COPY_QT_BINARIES(False False)

	#configure_file("${CMAKE_SOURCE_DIR}/setup/icon/windows/sourcetrail.ico" "${CMAKE_BINARY_DIR}/${CONFIGURATION}/sourcetrail.ico" COPYONLY)

endif()

set(SrcDir ${PROJECT_SOURCE_DIR}/src)

#add_subdirectory(${SrcDir}/gui/lon_widget)
set(LonWidgetSrc
	${SrcDir}/gui/lon_widget/autodeletewidgetpointer.hpp
	${SrcDir}/gui/lon_widget/button.hpp
	${SrcDir}/gui/lon_widget/listwidget.hpp
	${SrcDir}/gui/lon_widget/menu.hpp
	${SrcDir}/gui/lon_widget/messagebox.hpp
	${SrcDir}/gui/lon_widget/titlebar.hpp
	${SrcDir}/gui/lon_widget/widget.hpp
	${SrcDir}/gui/lon_widget/lon_widget.qrc
)

#所有源文件
set(TomatoSrc
	${SrcDir}/app/main.cpp
	${SrcDir}/gui/displayclockbase.h
	${SrcDir}/gui/mainwindow.cpp
	${SrcDir}/gui/mainwindow.h
	#fix
	${SrcDir}/gui/clock_main_widget/clockmainwidget.cpp
	${SrcDir}/gui/clock_main_widget/clockmainwidget.h
	${SrcDir}/gui/clock_small_window/clocksmallwindow.cpp
	${SrcDir}/gui/clock_small_window/clocksmallwindow.h
	${SrcDir}/gui/clock_small_window/progresswidget.cpp
	${SrcDir}/gui/clock_small_window/progresswidget.h
	${SrcDir}/gui/clock_small_window/toolswidget.cpp
	${SrcDir}/gui/clock_small_window/toolswidget.h
	${SrcDir}/gui/clock_subwidgets/addlabelwidget.cpp
	${SrcDir}/gui/clock_subwidgets/addlabelwidget.h
	${SrcDir}/gui/clock_subwidgets/addtargetwidget.cpp
	${SrcDir}/gui/clock_subwidgets/addtargetwidget.h
	${SrcDir}/gui/clock_subwidgets/chartswidget.h
	${SrcDir}/gui/clock_subwidgets/chartswidget.cpp
	${SrcDir}/gui/clock_subwidgets/clockdisplaywidget.cpp
	${SrcDir}/gui/clock_subwidgets/clockdisplaywidget.h
	${SrcDir}/gui/clock_subwidgets/clockrunningwidget.cpp
	${SrcDir}/gui/clock_subwidgets/clockrunningwidget.h
	${SrcDir}/gui/clock_subwidgets/customslicewithvalue.h
	${SrcDir}/gui/clock_subwidgets/labelsandtargetswidget.cpp
	${SrcDir}/gui/clock_subwidgets/labelsandtargetswidget.h
	${SrcDir}/gui/clock_subwidgets/piecharttest.hpp
	${SrcDir}/gui/clock_subwidgets/targetwidget.cpp
	${SrcDir}/gui/clock_subwidgets/targetwidget.h
	${SrcDir}/gui/qstringhash.h
	${SrcDir}/gui/settingfileoperations.cpp
	${SrcDir}/gui/settingfileoperations.h
	${SrcDir}/gui/settingwidget.h
	${SrcDir}/gui/settingwidget.cpp
	${SrcDir}/gui/temp.cpp
	${SrcDir}/gui/temp.h
	#fix
	${SrcDir}/gui/tomatoclocktimer.cpp
	${SrcDir}/gui/tomatoclocktimer.h
	${SrcDir}/utility/LonTypeDefines.h
	${SrcDir}/utility/clockoptions.hpp
	${SrcDir}/utility/TimeStatus.hpp
	${SrcDir}/utility/clock_database/clocksql.hpp
	${SrcDir}/utility/clock_database/DataStructure.hpp
	${LonWidgetSrc}
)

#头文件
set(TomatoMocHdr
)


#需要使用uic去编译的ui文件
set(TomatoUic
	${SrcDir}/gui/mainwindow.ui
	${SrcDir}/gui/temp.ui
	${SrcDir}/gui/settingwidget.ui
)

set(TomatoRes
	${PROJECT_SOURCE_DIR}/bin/res/gui/img.qrc
)

include_directories(${SrcDir}/utility)

link_directories()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CONFIGURATION}/${TARGET}")

add_executable(tomatoclock ${TomatoSrc} ${TomatoMocHdr} ${TomatoUic} ${TomatoRes})

if(UNIX)
	target_link_libraries(tomatoclock Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::PrintSupport Qt5::Sql Qt5::Charts pthread)
endif (UNIX)
if(WIN32)
	target_link_libraries(tomatoclock Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::PrintSupport Qt5::Sql Qt5::Charts)
endif (WIN32)

target_link_libraries(tomatoclock)

