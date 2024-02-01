# SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clauses

set(soundkonverter_codec_aften_SRCS
   soundkonverter_codec_aften.cpp
   aftencodecwidget.cpp
)

kcoreaddons_add_plugin(soundkonverter_codec_aften
    SOURCES ${soundkonverter_codec_aften_SRCS}
    INSTALL_NAMESPACE soundkonverterplugins/codecs)

target_link_libraries(soundkonverter_codec_aften KF6::WidgetsAddons Qt6::Xml soundkonvertercore)
