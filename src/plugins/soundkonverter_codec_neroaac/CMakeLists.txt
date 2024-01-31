project(soundkonverter_codec_neroaac)

set(soundkonverter_codec_neroaac_SRCS
   soundkonverter_codec_neroaac.cpp
   neroaaccodecwidget.cpp
)

add_library(soundkonverter_codec_neroaac MODULE ${soundkonverter_codec_neroaac_SRCS})
target_link_libraries(soundkonverter_codec_neroaac KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_codec_neroaac DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_codec_neroaac.desktop DESTINATION ${SERVICES_INSTALL_DIR})
