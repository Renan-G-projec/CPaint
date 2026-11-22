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
    Vector2 position;
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

void draw_canvas(Canvas *canvas);
void draw_canvas_from_history(Canvas *canvas);
void handle_brush_draw_input(Brush *brush, Canvas *canvas);
void draw_polyline(const Vector2* position, int qtd, float size, Color color);
bool save_canvas_to_file(Canvas *canvas, const char *filepath);
bool open_canvas_from_file(Canvas *canvas, const char* filepath);

void canvas_destroy(Canvas *canvas);

#endif