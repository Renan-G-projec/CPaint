// Ad Maiorem Dei Gloriam!

#include <stdio.h>
#include <raylib.h>
#include "canvas.h"

#define WINDOW_WIDTH 160 * 6
#define WINDOW_HEIGHT 90 * 6

typedef struct
{
    Vector2 *mouse_logs;
    size_t num_of_logs;
} DrawCommand;

typedef struct
{
    DrawCommand *data;
    size_t size;
} EditorHistory;


int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPaint");

    RenderTexture2D canvas = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

    float brush_size = DEFAULT_BRUSH_SIZE;

    SetTargetFPS(120);

    Vector2 mouse_position_tracker;
    bool is_first_click = false;

    while (!WindowShouldClose())
    {
        // Canvas
        BeginTextureMode(canvas);
        handle_brush_draw_input(brush_size, &is_first_click, &mouse_position_tracker);
        handle_brush_size_input(&brush_size);
        EndTextureMode();

        // Screen
        BeginDrawing();
        ClearBackground(BLACK);
        draw_canvas(&canvas, (Vector2){0, 0});
        draw_brush_target(brush_size);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
