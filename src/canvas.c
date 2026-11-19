// Ad Maiorem Dei Gloriam!

#include <raylib.h>
#include "canvas.h"
#include "history.h"


void draw_canvas(Canvas *canvas)
{
    DrawTextureRec(canvas->tex.texture, (Rectangle){0, 0, canvas->tex.texture.width, -canvas->tex.texture.height}, canvas->position, WHITE);
}

void draw_canvas_from_history(Canvas *canvas)
{
    const CanvasHistory *history = &(canvas->history);

    ClearBackground(BLACK);
    DrawTextureRec(history->old_history_initial_image, (Rectangle){0, 0, history->old_history_initial_image.width, -history->old_history_initial_image.height}, canvas->position, RAYWHITE);

    for (size_t idx = 0; idx <= history->old_history_stack_size; ++idx)
    {
        if (!history->old_history_stack[idx].mouse_logs) continue;
        draw_polyline(history->old_history_stack[idx].mouse_logs, history->old_history_stack[idx].num_of_logs, history->old_history_stack[idx].brush_size, history->old_history_stack[idx].brush_color);
    }
    
    if (history_undo_stack_is_empty(history)) return;
    for (int idx = history->undo_stack_tail; idx != history->undo_stack_head; idx = (idx + 1) % COMMAND_BUFFER_SIZE)
    {
        if (!history->undo_stack[idx].mouse_logs) continue;
        draw_polyline(history->undo_stack[idx].mouse_logs, history->undo_stack[idx].num_of_logs, history->undo_stack[idx].brush_size, history->undo_stack[idx].brush_color);
    }

    draw_canvas(canvas);
}

bool save_canvas_to_file(Canvas *canvas, const char *filepath)
{
    Image img = LoadImageFromTexture(canvas->tex.texture);
    ImageFlipVertical(&img);
    return ExportImage(img, filepath);
}

void draw_polyline(const Vector2 *positions, int qtd, float size, Color color)
{
    if (!positions || qtd == 0) return;

    DrawCircle(positions[0].x, positions[0].y, size, color);
    for (int i = 1; i < qtd; ++i)
    {
        DrawLineEx(positions[i - 1], positions[i], size * 2, color);
        DrawCircle(positions[i].x, positions[i].y, size, color);
    }
}

void handle_brush_draw_input(Brush *brush, Canvas *canvas)
{
    if (brush->is_locked) return;

    Vector2 mouse_pos = brush->current_pos;
    const Rectangle canvas_rect = {canvas->position.x, canvas->position.y, canvas->tex.texture.width, canvas->tex.texture.height};
    if (!CheckCollisionPointRec(mouse_pos, canvas_rect)) return;

    // First click
    if (brush->changed_size) {
        history_create_mouse_draw_command(&(canvas->history), brush->size, brush->color);
        return;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        history_clear_redo_stack(&(canvas->history));
        history_create_mouse_draw_command(&(canvas->history), brush->size, brush->color);
        return;
    }

    // Not First click
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        
        DrawLineEx(brush->last_pos, brush->current_pos, brush->size * 2, brush->color);
        
        DrawCircle(mouse_pos.x, mouse_pos.y, brush->size, brush->color);
        
        history_log_mouse_position(history_get_last_mouse_draw_command(&(canvas->history)), mouse_pos);
    }
}

void canvas_destroy(Canvas *canvas)
{
    history_destroy(&(canvas->history));
}