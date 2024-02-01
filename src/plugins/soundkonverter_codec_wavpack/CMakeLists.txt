# SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clauses

set(soundkonverter_codec_wavpack_SRCS
   soundkonverter_codec_wavpack.cpp
   wavpackcodecwidget.cpp
)

kcoreaddons_add_plugin(soundkonverter_codec_wavpack
    SOURCES ${soundkonverter_codec_wavpack_SRCS}
    INSTALL_NAMESPACE soundkonverterplugins/codecs)

target_link_libraries(soundkonverter_codec_wavpack KF6::WidgetsAddons Qt6::Xml soundkonvertercore)
