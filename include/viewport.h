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
    RenderTexture2D view;
    Color bg_color;
} Viewport;

Viewport viewport_init(Rectangle rect, Canvas *canvas);
void viewport_update(Viewport *viewport);
void viewport_render(Viewport *viewport);
void viewport_render_internal(Viewport *viewport);
bool viewport_is_mouse_over(Viewport *viewport);
void viewport_handle_mouse_input(Viewport *viewport); // OChanges the zoom and the offset by the mouse position, if the mouse is clicked.
bool viewport_is_mouse_over_canvas(Viewport *viewport);
Rectangle viewport_get_canvas_rect_global(Viewport *canvas);
Rectangle viewport_get_canvas_rect_local(Viewport *viewport);

#endif