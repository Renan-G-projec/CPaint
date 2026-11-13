// Ad Maiorem Dei Gloriam!

#include <raylib.h>
#include "canvas.h"
#include "history.h"


void draw_canvas(RenderTexture2D *canvas, Vector2 position)
{
    DrawTextureRec(canvas->texture, (Rectangle){0, 0, canvas->texture.width, -canvas->texture.height}, position, WHITE);
}

void draw_canvas_from_history(RenderTexture2D *canvas, Vector2 position, EditorHistory* history, float brush_size)
{
    ClearBackground(BLACK);
    if (history_undo_stack_is_empty(history)) return;

    printf("DRAW\nhead: %d | tail: %d\n", history->undo_stack_head, history->undo_stack_tail);
    for (int idx = history->undo_stack_tail; idx != history->undo_stack_head; idx = (idx + 1) % COMMAND_BUFFER_SIZE)
    {
        if (!history->undo_stack[idx].mouse_logs) continue;
        connect_mouse_positions_array(history->undo_stack[idx].mouse_logs, history->undo_stack[idx].num_of_logs, brush_size);
    }

    draw_canvas(canvas, position);
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

void connect_mouse_positions_array(const Vector2 *positions, int qtd, float brush_size)
{
    if (!positions || qtd == 0) return;

    DrawCircle(positions[0].x, positions[0].y, brush_size, RAYWHITE);
    for (int i = 1; i < qtd; ++i)
    {
        DrawLineEx(positions[i - 1], positions[i], brush_size * 2, RAYWHITE);
        DrawCircle(positions[i].x, positions[i].y, brush_size, RAYWHITE);
    }
}

void handle_brush_draw_input(float brush_size, bool *is_first_click_flag, Vector2 *mouse_position_tracker, EditorHistory *history)
{
    Vector2 mouse_pos = GetMousePosition();    

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if (*is_first_click_flag)
        {
            history_create_mouse_draw_command(history);
        }
        else
        {
            connect_mouse_positions(*mouse_position_tracker, mouse_pos, brush_size);
        }
        
        *is_first_click_flag = false;
        
        DrawCircle(mouse_pos.x, mouse_pos.y, brush_size, RAYWHITE);
        *mouse_position_tracker = mouse_pos;
        
        history_log_mouse_position(history_get_last_mouse_draw_command(history), mouse_pos);
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