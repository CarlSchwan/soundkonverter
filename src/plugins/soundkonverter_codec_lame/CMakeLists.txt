# SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clauses

set(soundkonverter_codec_lame_SRCS
   soundkonverter_codec_lame.cpp
   lamecodecwidget.cpp
   lameconversionoptions.cpp
)

kcoreaddons_add_plugin(soundkonverter_codec_lame
    SOURCES ${soundkonverter_codec_lame_SRCS}
    INSTALL_NAMESPACE soundkonverterplugins/codecs)

target_link_libraries(soundkonverter_codec_lame KF6::WidgetsAddons Qt6::Xml soundkonvertercore)
