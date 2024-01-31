project(soundkonverter_codec_opustools)

set(soundkonverter_codec_opustools_SRCS
   soundkonverter_codec_opustools.cpp
   opustoolscodecwidget.cpp
   opustoolsconversionoptions.cpp
)

add_library(soundkonverter_codec_opustools MODULE ${soundkonverter_codec_opustools_SRCS})
target_link_libraries(soundkonverter_codec_opustools KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_opustools DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_opustools.desktop DESTINATION ${SERVICES_INSTALL_DIR})
