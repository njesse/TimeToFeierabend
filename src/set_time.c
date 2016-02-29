#include "set_time.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static TextLayer *s_textlayer_h;
static TextLayer *s_textlayer_dp;
static TextLayer *s_textlayer_2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorClear);
 // window_set_fullscreen(s_window, false);
  
  // s_textlayer_h
  s_textlayer_h = text_layer_create(GRect(38, 46, 29, 29));
  text_layer_set_background_color(s_textlayer_h, GColorClear);
  text_layer_set_text_color(s_textlayer_h, GColorWhite);
  text_layer_set_text(s_textlayer_h, "12");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_h);
  
  // s_textlayer_dp
  s_textlayer_dp = text_layer_create(GRect(63, 45, 13, 20));
  text_layer_set_background_color(s_textlayer_dp, GColorClear);
  text_layer_set_text_color(s_textlayer_dp, GColorWhite);
  text_layer_set_text(s_textlayer_dp, ":");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_dp);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(81, 46, 30, 20));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text_color(s_textlayer_2, GColorWhite);
  text_layer_set_text(s_textlayer_2, "34");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_h);
  text_layer_destroy(s_textlayer_dp);
  text_layer_destroy(s_textlayer_2);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_set_time(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_set_time(void) {
  window_stack_remove(s_window, true);
}
