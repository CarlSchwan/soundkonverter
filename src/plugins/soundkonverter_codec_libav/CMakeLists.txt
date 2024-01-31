project(soundkonverter_codec_libav)

set(soundkonverter_codec_libav_SRCS
   soundkonverter_codec_libav.cpp
   libavcodecwidget.cpp
)

add_library(soundkonverter_codec_libav MODULE ${soundkonverter_codec_libav_SRCS})
target_link_libraries(soundkonverter_codec_libav KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_libav DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_libav.desktop DESTINATION ${SERVICES_INSTALL_DIR})
