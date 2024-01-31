project(soundkonverter_filter_sox)

set(soundkonverter_filter_sox_SRCS
   soundkonverter_filter_sox.cpp
   soxfilteroptions.cpp
   soxcodecwidget.cpp
   soxfilterwidget.cpp
   soxeffectwidget.cpp
)

add_library(soundkonverter_filter_sox MODULE ${soundkonverter_filter_sox_SRCS})
target_link_libraries(soundkonverter_filter_sox KF6::WidgetsAddons Qt6::Xml soundkonvertercore)

########### install files ###############

install(TARGETS soundkonverter_filter_sox DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES soundkonverter_filter_sox.desktop DESTINATION ${SERVICES_INSTALL_DIR})
