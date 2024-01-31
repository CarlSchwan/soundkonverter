project(soundkonverter_ripper_icedax)

set(soundkonverter_ripper_icedax_SRCS
   soundkonverter_ripper_icedax.cpp
)

add_library(soundkonverter_ripper_icedax MODULE ${soundkonverter_ripper_icedax_SRCS})
target_link_libraries(soundkonverter_ripper_icedax KF6::WidgetsAddons soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_ripper_icedax DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_ripper_icedax.desktop DESTINATION ${SERVICES_INSTALL_DIR})
