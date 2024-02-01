project(soundkonverter_replaygain_musepackgain)

set(soundkonverter_replaygain_musepackgain_SRCS
   soundkonverter_replaygain_musepackgain.cpp
)

add_library(soundkonverter_replaygain_musepackgain MODULE ${soundkonverter_replaygain_musepackgain_SRCS})
target_link_libraries(soundkonverter_replaygain_musepackgain KF6::WidgetsAddons soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_replaygain_musepackgain DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_replaygain_musepackgain.desktop DESTINATION ${SERVICES_INSTALL_DIR})
