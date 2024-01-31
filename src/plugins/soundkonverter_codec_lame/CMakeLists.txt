project(soundkonverter_codec_lame)

set(soundkonverter_codec_lame_SRCS
   soundkonverter_codec_lame.cpp
   lameconversionoptions.cpp
   lamecodecwidget.cpp
)

add_library(soundkonverter_codec_lame MODULE ${soundkonverter_codec_lame_SRCS})
target_link_libraries(soundkonverter_codec_lame KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_lame DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_lame.desktop DESTINATION ${SERVICES_INSTALL_DIR})
