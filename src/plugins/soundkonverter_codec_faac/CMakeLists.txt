project(soundkonverter_codec_faac)

set(soundkonverter_codec_faac_SRCS
   soundkonverter_codec_faac.cpp
   faaccodecwidget.cpp
)

add_library(soundkonverter_codec_faac MODULE ${soundkonverter_codec_faac_SRCS})
target_link_libraries(soundkonverter_codec_faac KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_faac DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_faac.desktop DESTINATION ${SERVICES_INSTALL_DIR})
