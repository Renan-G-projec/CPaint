// Ad Maiorem Dei Gloriam!
#ifndef GUI_H
#define GUI_H

#include <stdint.h>
#include <raylib.h>
#include "canvas.h"

typedef uint8_t gui_state_t;

#define GUI_CHANGE_COLOR_BUTTON_RECT (Rectangle){140.0f, 20.0f, 120.0f, 20.0f}

#define GUI_SAVE_BUTTON_RECT (Rectangle){270.0f, 20.0f, 100.0f, 20.0f}
#define GUI_COLOR_PICKER_RECT (Rectangle){140.0f, 40.0f, 280.0f, 280.0f}

typedef struct {
    // Dependencies and state
    Color *current_color;
    Canvas *current_canvas;

    bool is_picking_color;

    bool on_error;
    char error_buffer[128];

} GuiData;

GuiData gui_init(Color *current_color, Canvas *current_canvas);
void gui_update(GuiData *);

#endif