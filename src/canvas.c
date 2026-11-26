// Ad Maiorem Dei Gloriam!

#include <raylib.h>
#include "canvas.h"
#include "history_buffer.h"

bool canvas_save(Canvas *canvas, const char *filepath)
{
    Image img = LoadImageFromTexture(canvas->tex.texture);
    ImageFlipVertical(&img);
    bool success = ExportImage(img, filepath);
    UnloadImage(img);

    return success;
}

void canvas_draw_and_connect(Canvas *canvas, Vector2 position, float size, Color color)
{
    DrawCircleV(position, size, color);
    if (!canvas->is_drawing)
    {
        canvas->is_drawing = true;
        canvas->last_draw_position = position;

        history_buffer_clear(&(canvas->redo_buffer));
    }
    else
    {
        DrawLineEx(canvas->last_draw_position, position, size * 2, color);
        canvas->last_draw_position = position;
    }
}

void canvas_on_stop_drawing(Canvas *canvas)
{
    history_buffer_append(&(canvas->undo_buffer), canvas_take_snapshot(canvas));
}

void canvas_undo(Canvas *canvas)
{
    if (canvas->undo_buffer.size == 0) return;
    BeginTextureMode(canvas->tex);

    history_buffer_move(&(canvas->undo_buffer), &(canvas->redo_buffer));
    Texture2D *current_texture = history_buffer_top(&(canvas->undo_buffer));
    if (current_texture) {
        ClearBackground(PURPLE);
        DrawTexture(*current_texture, 0, 0, WHITE);
    }

    EndTextureMode();
}

void canvas_redo(Canvas *canvas)
{
    if (canvas->redo_buffer.size == 0) return;
    BeginTextureMode(canvas->tex);

    history_buffer_move(&(canvas->redo_buffer), &(canvas->undo_buffer));
    Texture2D *current_texture = history_buffer_top(&(canvas->undo_buffer));
    if (current_texture)
    {
        ClearBackground(PURPLE);
        DrawTexture(*current_texture, 0, 0, WHITE);
    }

    EndTextureMode();
}

void canvas_destroy(Canvas *canvas)
{
    if (canvas->filename) free(canvas->filename);
    history_buffer_clear(&(canvas->undo_buffer));
    history_buffer_clear(&(canvas->redo_buffer));
}

Texture2D canvas_take_snapshot(Canvas *canvas)
{
    Image snapshot_img = LoadImageFromTexture(canvas->tex.texture);
    ImageFlipVertical(&snapshot_img);
    Texture2D snapshot = LoadTextureFromImage(snapshot_img);
    UnloadImage(snapshot_img);

    return snapshot;
}