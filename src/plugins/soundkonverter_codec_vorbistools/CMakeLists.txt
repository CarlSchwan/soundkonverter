project(soundkonverter_codec_vorbistools)

set(soundkonverter_codec_vorbistools_SRCS
   soundkonverter_codec_vorbistools.cpp
   vorbistoolscodecwidget.cpp
)

add_library(soundkonverter_codec_vorbistools MODULE ${soundkonverter_codec_vorbistools_SRCS})
target_link_libraries(soundkonverter_codec_vorbistools KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_vorbistools DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_vorbistools.desktop DESTINATION ${SERVICES_INSTALL_DIR})
