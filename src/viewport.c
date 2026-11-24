// Ad Maiorem Dei Gloriam!
#include "viewport.h"

Viewport viewport_init(Rectangle rect, Canvas *canvas)
{
    Viewport viewport;

    viewport.rect = rect;
    viewport.zoom.x = 1.0;
    viewport.zoom.y = 1.0;
    viewport.offset.x = 0.0;
    viewport.offset.y = 0.0;

    viewport.canvas = canvas;
    viewport.view = LoadRenderTexture(rect.width, rect.height);

    viewport.zoom_sensitivity = 0.15f;

    viewport.bg_color = WHITE;
    viewport.is_dragging = false;

    return viewport;
}

void viewport_render(Viewport *viewport)
{
    Vector2 pos = {viewport->rect.x, viewport->rect.y};
    DrawTextureEx(viewport->view.texture, pos, 0.0f, 1.0f, WHITE);
}

void viewport_render_internal(Viewport *viewport)
{
    BeginTextureMode(viewport->view);

    ClearBackground(viewport->bg_color);

    Rectangle canvas_src = (Rectangle){0.0f, 0.0f, viewport->canvas->tex.texture.width, -viewport->canvas->tex.texture.height};\
    Rectangle canvas_dest = viewport_get_canvas_rect_local(viewport);
    DrawTexturePro(viewport->canvas->tex.texture, canvas_src, canvas_dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

    EndTextureMode();
}

void viewport_handle_mouse_input(Viewport *viewport)
{
    if (viewport->is_dragging)
    {
        Vector2 mouse_delta = GetMouseDelta();
        Vector2 mouse_delta_with_zoom = (Vector2){mouse_delta.x / viewport->zoom.x, mouse_delta.y / viewport->zoom.y};
        viewport->offset.x += mouse_delta_with_zoom.x;
        viewport->offset.y -= mouse_delta_with_zoom.y;

        if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) viewport->is_dragging = false;
    }
    else
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && viewport_is_mouse_over(viewport)) viewport->is_dragging = true;
    }

    float wheel_movement = GetMouseWheelMove();
    if (wheel_movement != 0 && !viewport->is_dragging && viewport_is_mouse_over(viewport))
    {
        viewport->zoom.x += viewport->zoom_sensitivity * wheel_movement;
        viewport->zoom.y += viewport->zoom_sensitivity * wheel_movement;

        viewport->zoom.x = viewport->zoom.x < VIEWPORT_MIN_ZOOM_FACTOR ? VIEWPORT_MIN_ZOOM_FACTOR : viewport->zoom.x;
        viewport->zoom.y = viewport->zoom.y < VIEWPORT_MIN_ZOOM_FACTOR ? VIEWPORT_MIN_ZOOM_FACTOR : viewport->zoom.y;
    }
}

bool viewport_is_mouse_over(Viewport *viewport)
{
    return CheckCollisionPointRec(GetMousePosition(), viewport->rect);
}


bool viewport_is_mouse_over_canvas(Viewport *viewport)
{
    return viewport_is_mouse_over(viewport) && CheckCollisionPointRec(GetMousePosition(), viewport_get_canvas_rect_global(viewport));
}

Rectangle viewport_get_canvas_rect_global(Viewport *viewport)
{
    if (!viewport->canvas) return (Rectangle){0};
    Rectangle local = viewport_get_canvas_rect_local(viewport);
    return (Rectangle){viewport->rect.x + local.x, viewport->rect.y + local.y, local.width, local.height};
}

Rectangle viewport_get_canvas_rect_local(Viewport *viewport) 
{
    if (!viewport->canvas) return (Rectangle){0};
    Vector2 middle_of_viewport = (Vector2){viewport->rect.width / 2, viewport->rect.height / 2};
    Vector2 offset_with_zoom = (Vector2){viewport->offset.x * viewport->zoom.x, viewport->offset.y * viewport->zoom.y};
    Vector2 canvas_rect_size = (Vector2){viewport->canvas->tex.texture.width * viewport->zoom.x, viewport->canvas->tex.texture.height * viewport->zoom.y};
    Rectangle canvas_rect = (Rectangle){middle_of_viewport.x + offset_with_zoom.x - (canvas_rect_size.x / 2.0f), middle_of_viewport.y + offset_with_zoom.y - (canvas_rect_size.y / 2.0f), canvas_rect_size.x, canvas_rect_size.y};
    return canvas_rect;
}