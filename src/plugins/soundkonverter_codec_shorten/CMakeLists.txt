project(soundkonverter_codec_shorten)

set(soundkonverter_codec_shorten_SRCS
   soundkonverter_codec_shorten.cpp
   shortencodecwidget.cpp
)

add_library(soundkonverter_codec_shorten MODULE ${soundkonverter_codec_shorten_SRCS})
target_link_libraries(soundkonverter_codec_shorten KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_shorten DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_shorten.desktop DESTINATION ${SERVICES_INSTALL_DIR})
