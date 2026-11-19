// Ad Maiorem Dei Gloriam!
#ifndef GUI_H
#define GUI_H

#include <raylib.h>
#include "canvas.h"

typedef enum {
    CPAINT_GUI_FREE,
    CPAINT_GUI_SAVE_NEW_CANVAS,
    CPAINT_GUI_DISCARD_CHANGES,
    CPAINT_GUI_CHANGING_COLOR,
} CPaintGuiState;

typedef struct {
    // Dependencies and state
    Color *current_color;
    Canvas *current_canvas;

    // Layout
    Rectangle color_picker_rec;
    Rectangle color_picker_toggle_rec;
    Rectangle save_new_canvas_rec;
    Rectangle save_new_canvas_input_rec;

    CPaintGuiState current_state;
    bool mouse_clicked_gui;

} GuiData;

GuiData gui_init(Vector2 screen_size, Color *current_color, Canvas *current_canvas);

void gui_render_all(GuiData *);
void gui_render_color_picker(Rectangle rect, Color *dest_color);

bool gui_is_click_consumed(Vector2 mouse_pos, GuiData *data);

#endif