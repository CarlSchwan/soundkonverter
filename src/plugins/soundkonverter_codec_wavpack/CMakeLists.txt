project(soundkonverter_codec_wavpack)

set(soundkonverter_codec_wavpack_SRCS
   soundkonverter_codec_wavpack.cpp
   wavpackcodecwidget.cpp
)

add_library(soundkonverter_codec_wavpack MODULE ${soundkonverter_codec_wavpack_SRCS})
target_link_libraries(soundkonverter_codec_wavpack KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_wavpack DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_wavpack.desktop DESTINATION ${SERVICES_INSTALL_DIR})
