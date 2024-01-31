project(soundkonverter_codec_fluidsynth)

set(soundkonverter_codec_fluidsynth_SRCS
   soundkonverter_codec_fluidsynth.cpp
   fluidsynthcodecwidget.cpp
)

add_library(soundkonverter_codec_fluidsynth MODULE ${soundkonverter_codec_fluidsynth_SRCS})
target_link_libraries(soundkonverter_codec_fluidsynth KF6::WidgetsAddons KF6::KIOCore Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_fluidsynth DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_fluidsynth.desktop DESTINATION ${SERVICES_INSTALL_DIR})
