// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef YARU_SETTINGS_PORTAL_H_
#define YARU_SETTINGS_PORTAL_H_

#include "yaru_settings.h"

G_BEGIN_DECLS

G_DECLARE_FINAL_TYPE(YaruSettingsPortal, yaru_settings_portal, YARU,
                     SETTINGS_PORTAL, GObject);

/**
 * YaruSettingsPortal:
 * #YaruSettingsPortal reads settings from the XDG desktop portal.
 */

/**
 * yaru_settings_portal_new:
 *
 * Creates a new settings portal instance.
 *
 * Returns: a new #YaruSettingsPortal.
 */
YaruSettingsPortal* yaru_settings_portal_new();

/**
 * yaru_settings_portal_new_with_values:
 * @values: (nullable): a #GVariantDict.
 *
 * Creates a new settings portal instance with initial values for testing.
 *
 * Returns: a new #YaruSettingsPortal.
 */
YaruSettingsPortal* yaru_settings_portal_new_with_values(
    GVariantDict* values);

/**
 * yaru_settings_portal_start:
 * @portal: an #YaruSettingsPortal.
 * @error: (allow-none): #GError location to store the error occurring, or %NULL
 *
 * Reads the current settings and starts monitoring for changes in the desktop
 * portal settings.
 *
 * Returns: %TRUE on success, or %FALSE if the portal is not available.
 */
gboolean yaru_settings_portal_start(YaruSettingsPortal* portal,
                                     GError** error);

G_END_DECLS

#endif  // YARU_SETTINGS_PORTAL_H_
