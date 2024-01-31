project(soundkonverter_codec_ffmpeg)

set(soundkonverter_codec_ffmpeg_SRCS
   soundkonverter_codec_ffmpeg.cpp
   ffmpegcodecwidget.cpp
)

add_library(soundkonverter_codec_ffmpeg MODULE ${soundkonverter_codec_ffmpeg_SRCS})
target_link_libraries(soundkonverter_codec_ffmpeg KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_ffmpeg DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_ffmpeg.desktop DESTINATION ${SERVICES_INSTALL_DIR})
