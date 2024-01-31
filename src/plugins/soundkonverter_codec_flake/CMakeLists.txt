project(soundkonverter_codec_flake)

set(soundkonverter_codec_flake_SRCS
   soundkonverter_codec_flake.cpp
   flakecodecwidget.cpp
)

add_library(soundkonverter_codec_flake MODULE ${soundkonverter_codec_flake_SRCS})
target_link_libraries(soundkonverter_codec_flake KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_flake DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_flake.desktop DESTINATION ${SERVICES_INSTALL_DIR})
