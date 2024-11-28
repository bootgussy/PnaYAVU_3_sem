cmake_minimum_required(VERSION 3.29)

project(CoffeeHouseSoftware)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64")

add_compile_options(-l sqlite3)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

qt6_wrap_ui(UI_HEADERS ${UI_FILES})


add_executable(CoffeeHouseSoftware
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    AnimatedButton.h AnimatedButton.cpp
    pics/logo.png
    resources.qrc
    signinwindow.h signinwindow.cpp signinwindow.ui
    loginwindow.h loginwindow.cpp loginwindow.ui
    pics/back_arrow.png
    Account.h Account.cpp
    Admin.h Admin.cpp
    Buyer.h Buyer.cpp
    Database.h Database.cpp
    Manager.h Manager.cpp
    Menu.h Menu.cpp
    MenuOption.h MenuOption.cpp
    Order.h Order.cpp
    Person.h
    sqlite3.h
    sqlite3.c
    CoffeeHouse.db
    buyerwindow.h buyerwindow.cpp buyerwindow.ui
    managerwindow.h managerwindow.cpp managerwindow.ui
    adminwindow.h adminwindow.cpp adminwindow.ui
    pics/cart_icon.png
    pics/points_icon.png
    marqueelabel.h marqueelabel.cpp
    cartwindow.h cartwindow.cpp
    itemlayout.h itemlayout.cpp
    changeoptionprice.h changeoptionprice.cpp
    categorieslist.h categorieslist.cpp
    custommessagebox.h custommessagebox.cpp
    changeoptiondiscount.h changeoptiondiscount.cpp
    chooseoptionwidget.h chooseoptionwidget.cpp
    leadershipwindow.h leadershipwindow.cpp




)
target_link_libraries(CoffeeHouseSoftware
        Qt::Core
        Qt::Gui
        Qt::Widgets
)


if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
