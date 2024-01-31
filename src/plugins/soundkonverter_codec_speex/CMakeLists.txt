project(soundkonverter_codec_speex)

set(soundkonverter_codec_speex_SRCS
   soundkonverter_codec_speex.cpp
   speexcodecwidget.cpp
)

add_library(soundkonverter_codec_speex MODULE ${soundkonverter_codec_speex_SRCS})
target_link_libraries(soundkonverter_codec_speex KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_speex DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_speex.desktop DESTINATION ${SERVICES_INSTALL_DIR})
