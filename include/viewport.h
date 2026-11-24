// Ad Maiorem Dei Gloriam!
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <raylib.h>
#include "canvas.h"

#define VIEWPORT_MIN_ZOOM_FACTOR 0.1f

typedef struct Viewport {
    Rectangle rect;
    Vector2 zoom;
    Vector2 offset; // WITHOUT THE ZOOM, this is a independent measure in pixels of how much far from the center of the viewport is the canvas

    Canvas *canvas;
    RenderTexture2D view;

    float zoom_sensitivity;

    Color bg_color;
    bool is_drawing_on_canvas;
    bool is_dragging;
} Viewport;

Viewport viewport_init(Rectangle rect, Canvas *canvas);
void viewport_update(Viewport *viewport);
void viewport_render(Viewport *viewport); // Draws the entire viewport, needs to habe called the viewport_render_internal first to render the canvas
void viewport_render_internal(Viewport *viewport); // Draws only the canvas and other viewport stuff inside the viewport
void viewport_handle_mouse_input(Viewport *viewport); // OChanges the zoom and the offset by the mouse position, if the mouse is clicked.
bool viewport_is_mouse_over(Viewport *viewport);
bool viewport_is_mouse_over_canvas(Viewport *viewport);
Rectangle viewport_get_canvas_rect_global(Viewport *canvas);
Rectangle viewport_get_canvas_rect_local(Viewport *viewport);

#endif