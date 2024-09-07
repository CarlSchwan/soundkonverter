
# include directories
include_directories(${CDPARANOIA_INCLUDE_DIR})

# soundkonvertercore
set(soundkonvertercore_SRCS
   core/backendplugin.cpp
   core/conversionoptions.cpp
   core/codecwidget.cpp
   core/codecplugin.cpp
   core/filterplugin.cpp
   core/replaygainplugin.cpp
   core/ripperplugin.cpp
)

add_library(soundkonvertercore SHARED ${soundkonvertercore_SRCS})
target_link_libraries(soundkonvertercore KF6::WidgetsAddons KF6::KIOFileWidgets KF6::KIOCore KF6::I18n KF6::StatusNotifierItem KF6::KCMUtils)

install(TARGETS soundkonvertercore DESTINATION ${LIB_INSTALL_DIR})

# soundkonverter
set(soundkonverter_SRCS
   configdialog/configdialog.cpp
   configdialog/configpagebase.cpp
   configdialog/configgeneralpage.cpp
   configdialog/configbackendspage.cpp
   configdialog/configadvancedpage.cpp
   configdialog/configcoverartpage.cpp
   metadata/tagengine.cpp
   metadata/MetaReplayGain.cpp
   opener/fileopener.cpp
   opener/diropener.cpp
   opener/cdopener.cpp
   opener/urlopener.cpp
   opener/playlistopener.cpp
   replaygainscanner/replaygainscanner.cpp
   replaygainscanner/replaygainfilelist.cpp
   replaygainscanner/replaygainfilelistitem.cpp
   replaygainscanner/replaygainprocessor.cpp
   global.cpp
   main.cpp
   soundkonverter.cpp
   soundkonverterview.cpp
   codecproblems.cpp
   codecoptimizations.cpp
   combobutton.cpp
   config.cpp
   conversionoptionsmanager.cpp
   convert.cpp
   convertitem.cpp
   filelist.cpp
   filelistitem.cpp
   logger.cpp
   logviewer.cpp
   options.cpp
   optionssimple.cpp
   optionsdetailed.cpp
   optionseditor.cpp
   optionslayer.cpp
   pluginloader.cpp
   progressindicator.cpp
   outputdirectory.cpp
   aboutplugins.cpp
   soundkonverter.qrc
)

add_executable(soundkonverter ${soundkonverter_SRCS})
target_link_libraries(soundkonverter
    PRIVATE
        KF6::WidgetsAddons
        KF6::KIOFileWidgets
        KF6::KIOCore
        KF6::Solid
        KF6::I18n
        KF6::XmlGui
        KCddb6
        Phonon::phonon4qt6
        Taglib::Taglib
        ${CDPARANOIA_LIBRARIES}
        soundkonvertercore
)

install(TARGETS soundkonverter ${KF6_INSTALL_TARGETS_DEFAULT_ARGS})

add_subdirectory(icons)
add_subdirectory(images)

# plugins
add_subdirectory(plugins)
