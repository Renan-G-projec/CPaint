// Ad Maiorem Dei Gloriam!
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <raylib.h>
#include "canvas.h"

typedef struct Viewport {
    Rectangle rect;
    Vector2 zoom;
    Vector2 offset;

    Canvas *canvas;
} Viewport;

Viewport viewport_init(Rectangle rect);
bool viewport_is_mouse_over(Viewport *viewport);
void viewport_handle_mouse_input(Viewport *viewport); // OChanges the zoom and the offset by the mouse position, if the mouse is clicked.
bool viewport_is_mouse_over_canvas(Viewport *viewport);
Rectangle viewport_get_canvas_rect(Viewport *viewport);

#endif