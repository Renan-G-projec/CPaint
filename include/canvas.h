// Ad Maiorem Dei Gloriam!
#ifndef CANVAS_H
#define CANVAS_H

#define DEFAULT_BRUSH_SIZE 10.0f
#define BRUSH_ADJUSTMENT_SIZE 1.0f
#define BRUSH_MINIMUM_SIZE 1.0f

#include "history.h"

typedef struct {
    RenderTexture2D tex;
    CanvasHistory history;

    bool drawing;
    Vector2 last_draw_position;

    char *filename;
    bool is_first_save;
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

bool canvas_save(Canvas *canvas, const char *filepath);
bool canvas_load(Canvas *canvas, const char *filepath);

void canvas_destroy(Canvas *canvas);

#endif