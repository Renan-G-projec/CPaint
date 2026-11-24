// Ad Maiorem Dei Gloriam!

#include <raylib.h>
#include "canvas.h"
#include "history.h"


bool canvas_save(Canvas *canvas, const char *filepath)
{
    Image img = LoadImageFromTexture(canvas->tex.texture);
    ImageFlipVertical(&img);
    return ExportImage(img, filepath);
}

void canvas_draw_and_connect(Canvas *canvas, Vector2 position, float size, Color color)
{
    DrawCircleV(position, size, color);
    if (!canvas->drawing)
    {
        canvas->drawing = true;
        canvas->last_draw_position = position;

        history_clear_redo_stack(&(canvas->history));
    }
    else
    {
        DrawLineEx(canvas->last_draw_position, position, size * 2, color);
        canvas->last_draw_position = position;
    }
}

void canvas_destroy(Canvas *canvas)
{
    history_destroy(&(canvas->history));
}