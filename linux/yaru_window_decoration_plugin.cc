#include "include/yaru_window_decoration/yaru_window_decoration_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>

#include "yaru_settings.h"

static void load_css(YaruSettings* settings) {
  GdkScreen* screen = gdk_screen_get_default();
  gpointer css_provider =
      g_object_get_data(G_OBJECT(screen), "_yaru_window_decoration_css_provider_");

  if (css_provider == nullptr) {
    css_provider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(
        screen, GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_set_data_full(G_OBJECT(screen), "_yaru_window_decoration_css_provider_",
                           css_provider, g_object_unref);
  }

  YaruColorScheme color_scheme = yaru_settings_get_color_scheme(settings);

  g_autoptr(GError) error = nullptr;
  g_autofree gchar* exe_path = g_file_read_link("/proc/self/exe", &error);
  g_autofree gchar* app_path = g_path_get_dirname(exe_path);
  const gchar* asset_path = "data/flutter_assets/packages/yaru_window_decoration/assets";
  const gchar* css_file = color_scheme == YARU_COLOR_SCHEME_DARK
                              ? "style-dark.css"
                              : "style.css";
  g_autofree gchar* css_path =
      g_build_filename(app_path, asset_path, css_file, nullptr);
  if (!gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(css_provider), css_path,
                                       &error)) {
    g_warning("%s: %s", css_path, error->message);
  }
}

void yaru_window_decoration_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  YaruSettings* settings = yaru_settings_new();
  load_css(settings);
  g_signal_connect_object(settings, "changed", G_CALLBACK(load_css), settings,
                          G_CONNECT_SWAPPED);
}
