// Ad Maiorem Dei Gloriam!
#include <raylib.h>
#include <raygui.h>
#include "filedialogue.h"
#include "cpaint.h"
#include "canvas.h"
#include "history.h"

void cpaint_start_loop(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPaint");

    SetTargetFPS(120);

    char file_to_save[256] = {0};

    Canvas canvas = {
        LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT),
        history_create(),
        {0, 0},
    };

    Brush brush = {
        {0, 0},
        {0, 0},
        DEFAULT_BRUSH_SIZE,
        false,
        false
    };

    bool is_on_file_dialogue = false;

    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    
    while (!WindowShouldClose())
    {
        // Canvas
        if (!is_on_file_dialogue)
        {
            brush.last_pos = brush.current_pos;
            brush.current_pos = GetMousePosition();

            BeginTextureMode(canvas.tex);
            handle_brush_draw_input(&brush, &canvas);
            
            if (IsKeyPressed(KEY_Z) && IsKeyDown(KEY_LEFT_CONTROL))
            {
                history_undo(&(canvas.history));
                draw_canvas_from_history(&canvas);
            }
            
            if (IsKeyPressed(KEY_Y) && IsKeyDown(KEY_LEFT_CONTROL))
            {
                history_redo(&(canvas.history));
                draw_canvas_from_history(&canvas);
            }
            EndTextureMode();

            if (IsKeyPressed(KEY_S) && IsKeyDown(KEY_LEFT_CONTROL))
            {
                is_on_file_dialogue = true;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
            
        // Screen
        BeginDrawing();
        ClearBackground(BLACK);
        draw_canvas(&canvas);

        if (is_on_file_dialogue)
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 100});

            const FiledialogueInput input = filedialogue_draw_and_get_inputs(file_to_save);
            if (input == FILEDIALOGUE_CLOSE) 
            {
                is_on_file_dialogue = false;
                SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
            }
            if (input == FILEDIALOGUE_SAVE)
            {
                is_on_file_dialogue = false;
                save_canvas_to_file(&canvas, file_to_save);
            }
        }

        EndDrawing();
    }
    canvas_destroy(&canvas);
    CloseWindow();
}