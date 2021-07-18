project(heera-desktop-daemon)

find_package(KF5WindowSystem REQUIRED)

add_executable(heera-desktop-daemon
    main.cpp
    desktopview.cpp
    settings.cpp
    qml.qrc
)

target_link_libraries(heera-desktop-daemon
    Qt5::Core
    Qt5::DBus
    Qt5::Widgets
    Qt5::Quick
    Qt5::QuickControls2
    KF5::WindowSystem
    HeeraUI
)
install(TARGETS heera-desktop-daemon RUNTIME DESTINATION /usr/bin)

file(GLOB TS_FILES translations/*.ts)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
add_custom_target(desktop-translations DEPENDS ${QM_FILES} SOURCES ${TS_FILES})
add_dependencies(heera-desktop-daemon desktop-translations)
install(FILES ${QM_FILES} DESTINATION /usr/share/heera-desktop-daemon/translations)
