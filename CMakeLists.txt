cmake_minimum_required(VERSION 3.16)
project(bytepurge VERSION 0.5.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20) # c++ version
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile_commands.json

include(GNUInstallDirs)

# libs import
find_package(PkgConfig REQUIRED)
find_package(nlohmann_json REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-3.0)
pkg_check_modules(APPINDICATOR REQUIRED IMPORTED_TARGET ayatana-appindicator3-0.1)

# source files
set(SOURCES
    src/main.cpp

    src/core/cleaner.cpp
    src/core/cli_tools.cpp
    src/core/config_loader.cpp
    src/core/constants.cpp
    src/core/signal_handler.cpp
    src/core/notifications_manager.cpp
    src/core/tray.cpp

    src/ui/css.cpp
    src/ui/main_window.cpp
    src/ui/message_dialog_helper.cpp
    src/ui/settings_window.cpp
    src/ui/ui_helper.cpp

    src/utils/args_parser.cpp
    src/utils/console_logger.cpp
    src/utils/system_detector.cpp
)

# compilation of all files
add_executable(${PROJECT_NAME} ${SOURCES})

# ccache compilation caching
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
endif()

# gresource
find_program(GLIB_COMPILE_RESOURCES glib-compile-resources)
if(GLIB_COMPILE_RESOURCES)
    set(GRESOURCE_XML ${CMAKE_CURRENT_SOURCE_DIR}/assets/resources.gresource.xml)
    set(GRESOURCE_C ${CMAKE_CURRENT_BINARY_DIR}/resources.c)

    add_custom_command(
        OUTPUT ${GRESOURCE_C}
        COMMAND ${GLIB_COMPILE_RESOURCES}
            --target=${GRESOURCE_C}
            --generate-source
            --sourcedir=${CMAKE_CURRENT_SOURCE_DIR}/assets
            ${GRESOURCE_XML}
        DEPENDS ${GRESOURCE_XML}
                ${CMAKE_CURRENT_SOURCE_DIR}/assets/categories.json
                ${CMAKE_CURRENT_SOURCE_DIR}/assets/package_managers.json
                ${CMAKE_CURRENT_SOURCE_DIR}/assets/app_style.css
                ${CMAKE_CURRENT_SOURCE_DIR}/assets/user_categories_template.json
        VERBATIM
    )

    add_library(resources OBJECT ${GRESOURCE_C})
    set_target_properties(resources PROPERTIES DISABLE_PRECOMPILE_HEADERS ON)
    target_link_libraries(resources PRIVATE PkgConfig::GTKMM)
    target_sources(${PROJECT_NAME} PRIVATE $<TARGET_OBJECTS:resources>)
else()
    message(WARNING "glib-compile-resources not found! Resources will not be embedded.")
endif()

# alias for modules/...
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE
    PkgConfig::GTKMM
    PkgConfig::APPINDICATOR
    nlohmann_json::nlohmann_json
)

target_precompile_headers(${PROJECT_NAME} PRIVATE
    <gtkmm.h>
    <giomm.h>
    <glibmm.h>
    <nlohmann/json.hpp>
)

# variables (macros)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    PROJECT_NAME="${PROJECT_NAME}"
    PROJECT_GENERIC_NAME="Byte Purge"
    PROJECT_VERSION="${PROJECT_VERSION}"
    PROJECT_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
)

# bytepurge command installment
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# .desktop file installment
install(FILES
    assets/bytepurge.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)

# svg (scalable) icon installment
install(FILES
    assets/icons/bytepurge.svg
    DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps
)

# png icon installment of different resolutions
set(ICON_SIZES 16 22 24 32 48 64 128 256 512)
foreach(SIZE ${ICON_SIZES})
    install(FILES
        assets/icons/bytepurge-${SIZE}.png
        DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/${SIZE}x${SIZE}/apps
    )
endforeach()
