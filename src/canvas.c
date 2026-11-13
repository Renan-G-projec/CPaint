// Ad Maiorem Dei Gloriam!

#include <raylib.h>
#include "canvas.h"


void draw_canvas(RenderTexture2D *canvas, Vector2 position)
{
    DrawTextureRec(canvas->texture, (Rectangle){0, 0, canvas->texture.width, -canvas->texture.height}, position, WHITE);
}

void draw_brush_target(float brush_size)
{
    Vector2 mouse_pos = GetMousePosition();

    DrawCircle(mouse_pos.x, mouse_pos.y, brush_size, RAYWHITE);
}

bool save_canvas_to_file(RenderTexture2D *canvas, const char *filepath)
{
    Image img = LoadImageFromTexture(canvas->texture);
    return ExportImage(img, filepath);
}

void handle_brush_size_input(float *dest)
{
    if (IsKeyPressed(KEY_EQUAL))
    {
        *dest += BRUSH_ADJUSTMENT_SIZE;
    }
    if (IsKeyPressed(KEY_MINUS))
    {
        *dest -= BRUSH_ADJUSTMENT_SIZE;
        if (*dest < BRUSH_MINIMUM_SIZE) *dest = BRUSH_MINIMUM_SIZE;
    }
}

void connect_mouse_positions(const Vector2 position_start, const Vector2 position_end, float brush_size)
{
    DrawLineEx(position_start, position_end, brush_size * 2, RAYWHITE);
}

void handle_brush_draw_input(float brush_size, bool *is_first_click_flag, Vector2 *mouse_position_tracker)
{
    Vector2 mouse_pos = GetMousePosition();    

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if (!*is_first_click_flag)
        {
            connect_mouse_positions(*mouse_position_tracker, mouse_pos, brush_size);
        }

        *is_first_click_flag = false;
        
        DrawCircle(mouse_pos.x, mouse_pos.y, brush_size, RAYWHITE);
        *mouse_position_tracker = mouse_pos;
    } 
    else 
    {
        *is_first_click_flag = true;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        ClearBackground(BLACK);
    }
}