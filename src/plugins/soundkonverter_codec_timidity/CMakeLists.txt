project(soundkonverter_codec_timidity)

set(soundkonverter_codec_timidity_SRCS
   soundkonverter_codec_timidity.cpp
   timiditycodecwidget.cpp
)

add_library(soundkonverter_codec_timidity MODULE ${soundkonverter_codec_timidity_SRCS})
target_link_libraries(soundkonverter_codec_timidity KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_timidity DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_timidity.desktop DESTINATION ${SERVICES_INSTALL_DIR})
