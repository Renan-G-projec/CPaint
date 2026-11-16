// Ad Maiorem Dei Gloriam!
#include <raylib.h>
#include <raygui.h>
#include "filedialogue.h"
#include "cpaint.h"
#include "canvas.h"
#include "history.h"

static char file_to_save[256] = {0};
static void cpaint_update_gui(CPaintState *state);

void cpaint_start_loop(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPaint");
    CPaintState state = {
        {
            LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT),
            history_create(),
            {0, 0},
        },
        {
            RAYWHITE,
            {0, 0},
            {0, 0},
            DEFAULT_BRUSH_SIZE,
            false,
            false
        },
        ON_MAIN_CANVAS
    };


    SetTargetFPS(120);

    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    
    while (!WindowShouldClose())
    {
        state.brush.last_pos = state.brush.current_pos;
        state.brush.current_pos = GetMousePosition();

            
        // Screen
        if (state.state == ON_MAIN_CANVAS)
        {
            BeginTextureMode(state.canvas.tex);
            handle_brush_draw_input(&(state.brush), &(state.canvas));

            if (IsKeyPressed(KEY_Z) && IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonUp(MOUSE_BUTTON_LEFT))
            {
                history_undo(&(state.canvas.history));
                draw_canvas_from_history(&(state.canvas));
            }
            
            if (IsKeyPressed(KEY_Y) && IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonUp(MOUSE_BUTTON_LEFT))
            {

                history_redo(&(state.canvas.history));
                draw_canvas_from_history(&(state.canvas));
            }
            EndTextureMode();
            
            if (IsKeyPressed(KEY_S) && IsKeyDown(KEY_LEFT_CONTROL))
            {
                state.state = ON_SAVE_DIALOGUE;
                state.brush.is_locked = true;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
            
        BeginDrawing();
        ClearBackground(BLACK);
        
        draw_canvas(&(state.canvas));

        cpaint_update_gui(&state);
        
        EndDrawing();
    }
    canvas_destroy(&(state.canvas));
    CloseWindow();
}

static void cpaint_update_gui(CPaintState *cpaint)
{
    switch(cpaint->state)
    {    
        case ON_SAVE_DIALOGUE:
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 100});

            const FiledialogueInput input = filedialogue_draw_and_get_inputs(file_to_save);
            if (input == FILEDIALOGUE_CLOSE) 
            {
                cpaint->state = ON_MAIN_CANVAS;
                cpaint->brush.is_locked = false;
                SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
            }
            if (input == FILEDIALOGUE_SAVE)
            {
                cpaint->state = ON_MAIN_CANVAS;
                cpaint->brush.is_locked = false;
                save_canvas_to_file(&(cpaint->canvas), file_to_save);
            }

            break;
        }
    }
}