// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef YARU_SETTINGS_H_
#define YARU_SETTINGS_H_

#include <glib-object.h>

G_BEGIN_DECLS

G_DECLARE_INTERFACE(YaruSettings, yaru_settings, YARU, SETTINGS, GObject)

/**
 * YaruColorScheme:
 * @YARU_COLOR_SCHEME_LIGHT: Prefer light theme.
 * @YARU_COLOR_SCHEME_DARK: Prefer dark theme.
 *
 * Available color schemes.
 */
typedef enum {
  YARU_COLOR_SCHEME_LIGHT,
  YARU_COLOR_SCHEME_DARK,
} YaruColorScheme;

/**
 * YaruSettings:
 * #YaruSettings is and object that provides desktop settings.
 */
struct _YaruSettingsInterface {
  GTypeInterface parent;
  YaruColorScheme (*get_color_scheme)(YaruSettings* settings);
};

/**
 * yaru_settings_new:
 *
 * Creates a new settings instance.
 *
 * Returns: a new #YaruSettings.
 */
YaruSettings* yaru_settings_new();

/**
 * yaru_settings_get_color_scheme:
 * @settings: an #YaruSettings.
 *
 * The preferred color scheme for the user interface.
 *
 * This corresponds to `org.gnome.desktop.interface.color-scheme` in GNOME.
 *
 * Returns: an #YaruColorScheme.
 */
YaruColorScheme yaru_settings_get_color_scheme(YaruSettings* settings);

/**
 * yaru_settings_emit_changed:
 * @settings: an #YaruSettings.
 *
 * Emits the "changed" signal. Used by YaruSettings implementations to notify
 * when the desktop settings have changed.
 */
void yaru_settings_emit_changed(YaruSettings* settings);

G_END_DECLS

#endif  // YARU_SETTINGS_H_
