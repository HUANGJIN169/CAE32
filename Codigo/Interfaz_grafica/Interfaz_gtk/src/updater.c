
#include "cae32_app.h"
#include <gtk/gtk.h>
// #include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GtkTextBuffer *buffer;
GtkTextIter start, end;
PangoFontDescription *font_desc;
GdkRGBA rgba;
GtkTextTag *tag;
GtkCssProvider *provider;
GtkStyleContext *context;
GtkTextIter nl;
GtkTextIter add_new_line(GtkTextBuffer *text_buffer, const gchar *text, GtkTextIter iter) {
  gtk_text_buffer_get_end_iter(text_buffer, &iter);
  gtk_text_buffer_insert(text_buffer, &iter, text, -1);
  gtk_text_buffer_insert(text_buffer, &iter, "\n", -1);
  return iter;
}
void test(GtkTextIter iter) { add_new_line(buffer, "lol", iter); }
int search_update(gpointer data) {
  // Check if already exists a update file
  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  char name[20];
  memset(name, 0, sizeof(name));
  int err;
  FILE *exists;
  exists = popen("ls .. | grep update", "r");
  if (exists == NULL) {
    g_printerr("ERROR\n");
    return -1;
  }

  while (fgets(name, 20, exists) != NULL) {
    g_printerr("%s", name);
  }
  g_printerr("%s", name);
  err = pclose(exists);
  if (err == -1)
    g_printerr("It can't be closed");

  if (strcmp(name, "updates.json") > 0) {
    g_printerr("updates.json found \nReading file"); // print on the textView
  } else {
    g_printerr("Didn't exists the update file"); // print on the textView
  }
  /*
  GtkTextIter *start = NULL;
  GtkTextTag *updatelog = gtk_text_tag_new("f");
  GtkTextTagTable *t_updatelog = gtk_text_tag_table_new();
  GtkTextBuffer *buffer_update = gtk_text_buffer_new(t_updatelog);
  gtk_text_buffer_get_end_iter(buffer_update, start);
  gtk_text_buffer_insert(buffer_update, start, name, sizeof(name));
  gtk_text_view_set_buffer(GTK_TEXT_VIEW(UI->tv_updatelog), buffer_update);


  GtkTextBuffer *buffer_update = gtk_text_view_get_buffer(GTK_TEXT_VIEW(UI->tv_updatelog));
  gtk_text_buffer_set_text(buffer_update, "Hello, world!", -1);
  return 0;
  */
  // GtkWidget *view;

  // view = gtk_text_view_new();

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(UI->tv_updatelog));

  gtk_text_buffer_set_text(buffer, "Hello, this is some text\n", -1);

  /* Change default font and color throughout the widget */
  provider = gtk_css_provider_new();
  gtk_css_provider_load_from_data(provider,
                                  "textview {"
                                  " font-family: serif;"
                                  "  color: green;"
                                  "  font-size:30px;"
                                  "}",
                                  -1, NULL);
  context = gtk_widget_get_style_context(UI->tv_updatelog);
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  /* Change left margin throughout the widget */
  gtk_text_view_set_left_margin(GTK_TEXT_VIEW(UI->tv_updatelog), 30);

  /* Use a tag to change the color for just one part of the widget */
  tag = gtk_text_buffer_create_tag(buffer, "blue_foreground", "foreground", "blue", NULL);
  gtk_text_buffer_get_iter_at_offset(buffer, &start, 7);
  gtk_text_buffer_get_iter_at_offset(buffer, &end, 12);
  gtk_text_buffer_apply_tag(buffer, tag, &start, &end);
  // gtk_text_buffer_get_end_iter(buffer, &end);
  // gtk_text_buffer_insert(buffer, &end, "tribute\n", -1);
  nl = add_new_line(buffer, "rupert", end);
  nl = add_new_line(buffer, "metal", nl);
  nl = add_new_line(buffer, "kyle", nl);
  test(nl);
  return 0;
}

// system("wget https://github.com/janc18/CAE32/raw/main/Codigo/Interfaz_grafica/Interfaz_gtk/updates.json -O ~/.pccae32/updates.json -q -nc && echo
// " "OK || echo ERROR");
