cmake_minimum_required(VERSION 3.16)

project(sea_analysis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Gui Graphs)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appsea_analysis
    main.cpp
)

qt_add_qml_module(appsea_analysis
    URI SeaAnalysis
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
    WaveDataProvider.h WaveDataProvider.cpp
        QML_FILES SeaSurfaceForm.ui.qml
    QML_FILES SeaSurface.qml
    SOURCES WaveDataWorker.h WaveDataWorker.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appsea_analysis PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appsea_analysis
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appsea_analysis
    PRIVATE Qt6::Quick Qt6::Gui Qt6::Graphs
)

include(GNUInstallDirs)
install(TARGETS appsea_analysis
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
