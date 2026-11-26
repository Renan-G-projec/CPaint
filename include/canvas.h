// Ad Maiorem Dei Gloriam!
#ifndef CANVAS_H
#define CANVAS_H

#define DEFAULT_BRUSH_SIZE 10.0f
#define BRUSH_ADJUSTMENT_SIZE 1.0f
#define BRUSH_MINIMUM_SIZE 1.0f

#include "history_buffer.h"
#include "dynamic_string.h"

typedef struct {
    RenderTexture2D tex;
    HistoryBuffer undo_buffer;
    HistoryBuffer redo_buffer;

    bool is_drawing;
    Vector2 last_draw_position;

    bool is_first_save;
    CPaintDynamicString filename;
} Canvas;

typedef struct {
    Color color;
    Vector2 current_pos;
    Vector2 last_pos;
    float size;
    bool changed_size;
    bool is_locked; 
} Brush;

void canvas_draw_and_connect(Canvas *canvas, Vector2 position, float size, Color color);
void canvas_on_stop_drawing(Canvas *canvas);

void canvas_undo(Canvas *canvas);
void canvas_redo(Canvas *canvas);

bool canvas_save(Canvas *canvas, const char *filepath);
bool canvas_load(Canvas *canvas, const char *filepath);

void canvas_destroy(Canvas *canvas);
Texture2D canvas_take_snapshot(Canvas *canvas);

#endif