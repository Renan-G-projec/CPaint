// Ad Maiorem Dei Gloriam!
#ifndef CANVAS_H
#define CANVAS_H

#define DEFAULT_BRUSH_SIZE 10.0f
#define BRUSH_ADJUSTMENT_SIZE 1.0f
#define BRUSH_MINIMUM_SIZE 1.0f

#include "history.h"

void draw_canvas(RenderTexture2D *canvas, Vector2 position);
void draw_canvas_from_history(RenderTexture2D *canvas, Vector2 position, EditorHistory* history, float brush_size);
void handle_brush_size_input(float *dest);
void handle_brush_draw_input(float brush_size, bool *is_first_click_flag, Vector2 *mouse_position_tracker, EditorHistory* history);
void connect_mouse_positions(const Vector2 position_start, const Vector2 position_end, float brush_size);
void connect_mouse_positions_array(const Vector2* position, int qtd, float brush_size);
void draw_brush_target(float brush_size);
bool save_canvas_to_file(RenderTexture2D *canvas, const char *filepath);

#endif