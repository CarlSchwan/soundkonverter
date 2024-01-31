project(soundkonverter_codec_mplayer)

set(soundkonverter_codec_mplayer_SRCS
   soundkonverter_codec_mplayer.cpp
)

add_library(soundkonverter_codec_mplayer MODULE ${soundkonverter_codec_mplayer_SRCS})
target_link_libraries(soundkonverter_codec_mplayer KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_mplayer DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_mplayer.desktop DESTINATION ${SERVICES_INSTALL_DIR})
