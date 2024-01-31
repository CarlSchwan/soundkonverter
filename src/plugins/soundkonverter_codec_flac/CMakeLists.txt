project(soundkonverter_codec_flac)

set(soundkonverter_codec_flac_SRCS
   soundkonverter_codec_flac.cpp
   flaccodecwidget.cpp
)

add_library(soundkonverter_codec_flac MODULE ${soundkonverter_codec_flac_SRCS})
target_link_libraries(soundkonverter_codec_flac KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_flac DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_flac.desktop DESTINATION ${SERVICES_INSTALL_DIR})
