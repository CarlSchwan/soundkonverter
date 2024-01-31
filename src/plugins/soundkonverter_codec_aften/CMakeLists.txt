project(soundkonverter_codec_aften)

set(soundkonverter_codec_aften_SRCS
   soundkonverter_codec_aften.cpp
   aftencodecwidget.cpp
)

add_library(soundkonverter_codec_aften MODULE ${soundkonverter_codec_aften_SRCS})
target_link_libraries(soundkonverter_codec_aften KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_aften DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_aften.desktop DESTINATION ${KDE_INSTALL_PLUGINDIR})
