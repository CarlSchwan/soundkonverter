# SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clauses

set(soundkonverter_codec_fluidsynth_SRCS
   soundkonverter_codec_fluidsynth.cpp
   fluidsynthcodecwidget.cpp
)

kcoreaddons_add_plugin(soundkonverter_codec_fluidsynth
    SOURCES ${soundkonverter_codec_fluidsynth_SRCS}
    INSTALL_NAMESPACE soundkonverterplugins/codecs)

target_link_libraries(soundkonverter_codec_fluidsynth KF6::WidgetsAddons Qt6::Xml soundkonvertercore)
