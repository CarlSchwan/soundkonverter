project(soundkonverter_replaygain_metaflac)

set(soundkonverter_replaygain_metaflac_SRCS
   soundkonverter_replaygain_metaflac.cpp
)

add_library(soundkonverter_replaygain_metaflac MODULE ${soundkonverter_replaygain_metaflac_SRCS})
target_link_libraries(soundkonverter_replaygain_metaflac KF6::WidgetsAddons soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_replaygain_metaflac DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_replaygain_metaflac.desktop DESTINATION ${SERVICES_INSTALL_DIR})
