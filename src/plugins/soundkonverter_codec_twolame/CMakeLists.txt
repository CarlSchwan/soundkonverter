project(soundkonverter_codec_twolame)

set(soundkonverter_codec_twolame_SRCS
   soundkonverter_codec_twolame.cpp
   twolamecodecwidget.cpp
)

add_library(soundkonverter_codec_twolame MODULE ${soundkonverter_codec_twolame_SRCS})
target_link_libraries(soundkonverter_codec_twolame KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_twolame DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_twolame.desktop DESTINATION ${SERVICES_INSTALL_DIR})
