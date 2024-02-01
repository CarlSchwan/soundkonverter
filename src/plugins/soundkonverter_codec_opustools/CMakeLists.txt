# SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
# SPDX-License-Identifier: BSD-2-Clauses

set(soundkonverter_codec_opustools_SRCS
   soundkonverter_codec_opustools.cpp
   opustoolscodecwidget.cpp
   opustoolsconversionoptions.cpp
)

kcoreaddons_add_plugin(soundkonverter_codec_opustools
    SOURCES ${soundkonverter_codec_opustools_SRCS}
    INSTALL_NAMESPACE soundkonverterplugins/codecs)

target_link_libraries(soundkonverter_codec_opustools KF6::WidgetsAddons Qt6::Xml soundkonvertercore)
