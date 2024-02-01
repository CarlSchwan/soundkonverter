# SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clauses

set(soundkonverter_codec_neroaac_SRCS
   soundkonverter_codec_neroaac.cpp
   neroaaccodecwidget.cpp
)

kcoreaddons_add_plugin(soundkonverter_codec_neroaac
    SOURCES ${soundkonverter_codec_neroaac_SRCS}
    INSTALL_NAMESPACE soundkonverterplugins/codecs)

target_link_libraries(soundkonverter_codec_neroaac KF6::WidgetsAddons Qt6::Xml soundkonvertercore)
