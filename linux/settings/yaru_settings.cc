// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "yaru_settings.h"

#include "yaru_gnome_settings.h"
#include "yaru_settings_portal.h"

G_DEFINE_INTERFACE(YaruSettings, yaru_settings, G_TYPE_OBJECT)

enum {
  kSignalChanged,
  kSignalLastSignal,
};

static guint signals[kSignalLastSignal];

static void yaru_settings_default_init(YaruSettingsInterface* iface) {
  /**
   * YaruSettings::changed:
   * @settings: an #YaruSettings
   *
   * This signal is emitted after the settings have been changed.
   */
  signals[kSignalChanged] =
      g_signal_new("changed", G_TYPE_FROM_INTERFACE(iface), G_SIGNAL_RUN_LAST,
                   0, NULL, NULL, NULL, G_TYPE_NONE, 0);
}

YaruColorScheme yaru_settings_get_color_scheme(YaruSettings* self) {
  return YARU_SETTINGS_GET_IFACE(self)->get_color_scheme(self);
}

void yaru_settings_emit_changed(YaruSettings* self) {
  g_return_if_fail(YARU_IS_SETTINGS(self));
  g_signal_emit(self, signals[kSignalChanged], 0);
}

YaruSettings* yaru_settings_new() {
  g_autoptr(YaruSettingsPortal) portal = yaru_settings_portal_new();

  g_autoptr(GError) error = nullptr;
  if (!yaru_settings_portal_start(portal, &error)) {
    g_debug("XDG desktop portal settings unavailable: %s", error->message);
    return yaru_gnome_settings_new();
  }

  return YARU_SETTINGS(g_object_ref(portal));
}
