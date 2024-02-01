project(soundkonverter_replaygain_aacgain)

set(soundkonverter_replaygain_aacgain_SRCS
   soundkonverter_replaygain_aacgain.cpp
)

add_library(soundkonverter_replaygain_aacgain MODULE ${soundkonverter_replaygain_aacgain_SRCS})
target_link_libraries(soundkonverter_replaygain_aacgain KF6::WidgetsAddons soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_replaygain_aacgain DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_replaygain_aacgain.desktop DESTINATION ${SERVICES_INSTALL_DIR})
