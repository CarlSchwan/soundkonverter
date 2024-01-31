project(soundkonverter_replaygain_wvgain)

set(soundkonverter_replaygain_wvgain_SRCS
   soundkonverter_replaygain_wvgain.cpp
)

add_library(soundkonverter_replaygain_wvgain MODULE ${soundkonverter_replaygain_wvgain_SRCS})
target_link_libraries(soundkonverter_replaygain_wvgain KF6::WidgetsAddons soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_replaygain_wvgain DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_replaygain_wvgain.desktop DESTINATION ${SERVICES_INSTALL_DIR})
