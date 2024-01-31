# SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
# SPDX-License-Identifier: BSD-2-Clause

project(soundkonverter)
cmake_minimum_required(VERSION 3.16)

set(KF_MIN_VERSION "5.240.0")
set(QT_MIN_VERSION "6.5")
set(TAGLIB_MIN_VERSION "1.11.1")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

include(FeatureSummary)
include(ECMSetupVersion)
include(KDEInstallDirs)
include(ECMFindQmlModule)
include(KDEClangFormat)
include(ECMQtDeclareLoggingCategory)
include(KDECMakeSettings)
#include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMAddTests)
include(ECMInstallIcons)
include(KDEGitCommitHooks)

find_package(Qt6 ${QT_MIN_VERSION} NO_MODULE COMPONENTS Widgets Core Xml)
set_package_properties(Qt6 PROPERTIES
    TYPE REQUIRED
    PURPOSE "Required application components"
)

find_package(KF6 ${KF_MIN_VERSION} COMPONENTS I18n XmlGui KIO Solid Config ConfigWidgets WidgetsAddons StatusNotifierItem)
set_package_properties(KF6 PROPERTIES
    TYPE REQUIRED
    PURPOSE "Required application components"
)

find_package(KCddb6 REQUIRED)
find_package(Phonon4Qt6 REQUIRED)
find_package(Cdparanoia REQUIRED)
find_package(Taglib ${TAGLIB_MIN_VERSION} REQUIRED)

add_subdirectory(src)
ki18n_install(po)

# include directories
include_directories(${CDPARANOIA_INCLUDE_DIR})

install(FILES org.kde.soundkonverter.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.soundkonverter.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})

# summary
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

# clang format
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.h)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
