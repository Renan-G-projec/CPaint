// Ad Maiorem Dei Gloriam!

#include <stdio.h>
#include <raylib.h>
#include "filedialogue.h"
#include "canvas.h"
#include "history.h"

#define WINDOW_WIDTH 160 * 6
#define WINDOW_HEIGHT 90 * 6


int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPaint");

    RenderTexture2D canvas = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

    float brush_size = DEFAULT_BRUSH_SIZE;

    SetTargetFPS(120);

    Vector2 mouse_position_tracker;
    bool is_first_click = false;
    bool is_on_file_dialogue = false;

    EditorHistory h = history_create();
    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    
    while (!WindowShouldClose())
    {
        // Canvas
        if (!is_on_file_dialogue)
        {
            BeginTextureMode(canvas);
            handle_brush_draw_input(brush_size, &is_first_click, &mouse_position_tracker, &h);
            handle_brush_size_input(&brush_size);
            
            if (IsKeyPressed(KEY_Z) && IsKeyDown(KEY_LEFT_CONTROL))
            {
                history_undo(&h);
                draw_canvas_from_history(&canvas, (Vector2){0, 0}, &h, brush_size);
            }
            
            if (IsKeyPressed(KEY_Y) && IsKeyDown(KEY_LEFT_CONTROL))
            {
                history_redo(&h);
                draw_canvas_from_history(&canvas, (Vector2){0, 0}, &h, brush_size);
            }
            EndTextureMode();

            if (IsKeyPressed(KEY_S) && IsKeyDown(KEY_LEFT_CONTROL))
            {
                is_on_file_dialogue = true;
                is_first_click = true;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
            
        // Screen
        BeginDrawing();
        ClearBackground(BLACK);
        draw_canvas(&canvas, (Vector2){0, 0});

        if (is_on_file_dialogue)
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 100});
            filedialogue_draw_dialogue();
            
            const FiledialogueInput input = filedialogue_get_inputs();
            if (input == FILEDIALOGUE_CLOSE) 
            {
                is_on_file_dialogue = false;
                SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
            }
            else if (input == FILEDIALOGUE_SAVE)
            {
                is_on_file_dialogue = false;
                save_canvas_to_file(&canvas, "./build/save.png");
                break;
            }
        }

        EndDrawing();
    }
    history_destroy(&h);
    CloseWindow();
    return 0;
}
