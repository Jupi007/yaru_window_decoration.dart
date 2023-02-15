// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef YARU_GNOME_SETTINGS_H_
#define YARU_GNOME_SETTINGS_H_

#include "yaru_settings.h"

G_BEGIN_DECLS

G_DECLARE_FINAL_TYPE(YaruGnomeSettings, yaru_gnome_settings, YARU,
                     GNOME_SETTINGS, GObject);

/**
 * yaru_gnome_settings_new:
 *
 * Creates a new settings instance for GNOME.
 *
 * Returns: a new #YaruSettings.
 */
YaruSettings* yaru_gnome_settings_new();

G_END_DECLS

#endif  // YARU_GNOME_SETTINGS_H_
