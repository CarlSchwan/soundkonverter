# SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clauses

set(soundkonverter_codec_libav_SRCS
   soundkonverter_codec_libav.cpp
   libavcodecwidget.cpp
)

kcoreaddons_add_plugin(soundkonverter_codec_libav
    SOURCES ${soundkonverter_codec_libav_SRCS}
    INSTALL_NAMESPACE soundkonverterplugins/codecs)

target_link_libraries(soundkonverter_codec_libav KF6::WidgetsAddons Qt6::Xml soundkonvertercore)
