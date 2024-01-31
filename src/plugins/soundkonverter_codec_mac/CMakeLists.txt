project(soundkonverter_codec_mac)

set(soundkonverter_codec_mac_SRCS
   soundkonverter_codec_mac.cpp
   maccodecwidget.cpp
)

add_library(soundkonverter_codec_mac MODULE ${soundkonverter_codec_mac_SRCS})
target_link_libraries(soundkonverter_codec_mac KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_mac DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_mac.desktop DESTINATION ${SERVICES_INSTALL_DIR})
