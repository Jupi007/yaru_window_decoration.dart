// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "yaru_gnome_settings.h"

#include <gio/gio.h>
#include <glib.h>

static constexpr char kDesktopInterfaceSchema[] = "org.gnome.desktop.interface";
static constexpr char kDesktopGtkThemeKey[] = "gtk-theme";

static constexpr char kGtkThemeDarkSuffix[] = "-dark";
static constexpr char kInterfaceSettings[] = "interface-settings";

struct _YaruGnomeSettings {
  GObject parent_instance;

  GSettings* interface_settings;
};

enum { kProp0, kPropInterfaceSettings, kPropLast };

static void yaru_gnome_settings_iface_init(YaruSettingsInterface* iface);

G_DEFINE_TYPE_WITH_CODE(YaruGnomeSettings, yaru_gnome_settings, G_TYPE_OBJECT,
                        G_IMPLEMENT_INTERFACE(yaru_settings_get_type(),
                                              yaru_gnome_settings_iface_init))

static YaruColorScheme yaru_gnome_settings_get_color_scheme(
    YaruSettings* settings) {
  YaruGnomeSettings* self = YARU_GNOME_SETTINGS(settings);

  YaruColorScheme color_scheme = YARU_COLOR_SCHEME_LIGHT;

  if (self->interface_settings != nullptr) {
    // check whether org.gnome.desktop.interface.gtk-theme ends with "-dark"
    g_autofree gchar* value =
        g_settings_get_string(self->interface_settings, kDesktopGtkThemeKey);
    if (g_str_has_suffix(value, kGtkThemeDarkSuffix)) {
      color_scheme = YARU_COLOR_SCHEME_DARK;
    }
  }
  return color_scheme;
}

static void yaru_gnome_settings_set_interface_settings(
    YaruGnomeSettings* self, GSettings* settings) {
  g_return_if_fail(G_IS_SETTINGS(settings));

  g_signal_connect_object(settings, "changed::gtk-theme",
                          G_CALLBACK(yaru_settings_emit_changed), self,
                          G_CONNECT_SWAPPED);

  self->interface_settings = G_SETTINGS(g_object_ref(settings));
}

static void yaru_gnome_settings_set_property(GObject* object, guint prop_id,
                                              const GValue* value,
                                              GParamSpec* pspec) {
  YaruGnomeSettings* self = YARU_GNOME_SETTINGS(object);
  switch (prop_id) {
    case kPropInterfaceSettings:
      yaru_gnome_settings_set_interface_settings(
          self, G_SETTINGS(g_value_get_object(value)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

static void yaru_gnome_settings_dispose(GObject* object) {
  YaruGnomeSettings* self = YARU_GNOME_SETTINGS(object);

  g_clear_object(&self->interface_settings);

  G_OBJECT_CLASS(yaru_gnome_settings_parent_class)->dispose(object);
}

static void yaru_gnome_settings_class_init(YaruGnomeSettingsClass* klass) {
  GObjectClass* object_class = G_OBJECT_CLASS(klass);
  object_class->dispose = yaru_gnome_settings_dispose;
  object_class->set_property = yaru_gnome_settings_set_property;

  g_object_class_install_property(
      object_class, kPropInterfaceSettings,
      g_param_spec_object(
          kInterfaceSettings, kInterfaceSettings, kDesktopInterfaceSchema,
          g_settings_get_type(),
          static_cast<GParamFlags>(G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY |
                                   G_PARAM_STATIC_STRINGS)));
}

static void yaru_gnome_settings_iface_init(YaruSettingsInterface* iface) {
  iface->get_color_scheme = yaru_gnome_settings_get_color_scheme;
}

static void yaru_gnome_settings_init(YaruGnomeSettings*) {}

static GSettings* create_settings(const gchar* schema_id) {
  GSettings* settings = nullptr;
  GSettingsSchemaSource* source = g_settings_schema_source_get_default();
  if (source != nullptr) {
    g_autoptr(GSettingsSchema) schema =
        g_settings_schema_source_lookup(source, schema_id, TRUE);
    if (schema != nullptr) {
      settings = g_settings_new_full(schema, nullptr, nullptr);
    }
  }
  return settings;
}

YaruSettings* yaru_gnome_settings_new() {
  g_autoptr(GSettings) interface_settings =
      create_settings(kDesktopInterfaceSchema);
  return YARU_SETTINGS(g_object_new(yaru_gnome_settings_get_type(),
                                     kInterfaceSettings, interface_settings,
                                     nullptr));
}
