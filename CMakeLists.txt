cmake_minimum_required(VERSION 3.16)

project(MusicPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Multimedia)

qt_standard_project_setup()

qt_add_executable(appMusicPlayer
    main.cpp
)

qt_add_qml_module(appMusicPlayer
    URI MusicPlayer
    VERSION 1.0
    QML_FILES Main.qml AudioInfoBox.qml ImageButton.qml ProgressBar.qml PlaylistPanel.qml SearchField.qml SearchPanel.qml VolumeBar.qml

    SOURCES PlayerController.h PlayerController.cpp  AudioInfo.h AudioInfo.cpp AudioSearchModel.h AudioSearchModel.cpp

    RESOURCES
    assets/icons/logo.png
    assets/icons/play-btn.png
    assets/icons/pause-btn.png
    assets/icons/next-btn.png
    assets/icons/previous-btn.png
    assets/icons/loop-disabled-btn.png
    assets/icons/loop-enabled-btn.png
    assets/icons/random-disabled-btn.png
    assets/icons/random-enabled-btn.png
    assets/icons/delete-btn.png
    assets/icons/add-btn.png
    assets/icons/cancel-btn.png
    assets/icons/search-btn.png
    assets/icons/volume-btn.png
    assets/icons/mute-btn.png

    assets/images/song1.png
    assets/images/song2.jpg
    assets/images/song3.jpg
    assets/images/song4.png

    assets/audios/song1.mp3
    assets/audios/song2.mp3
    assets/audios/song3.mp3
    assets/audios/song4.mp3
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMusicPlayer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMusicPlayer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMusicPlayer
    PRIVATE Qt6::Quick Qt6::Multimedia
)

include(GNUInstallDirs)
install(TARGETS appMusicPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
