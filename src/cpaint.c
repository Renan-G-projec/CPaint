// Ad Maiorem Dei Gloriam!
#include <raylib.h>
#include <raygui.h>
#include <string.h>
#include <nvdialog.h>
#include "cpaint.h"
#include "canvas.h"
#include "history_buffer.h"

#include "gui.h"
void cpaint_start_loop(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPaint");
    CPaintState state = {
        {
            LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT),
            history_create(),
            {0, 0},
            NULL,
            true,
        },
        {
            RAYWHITE,
            {0, 0},
            {0, 0},
            DEFAULT_BRUSH_SIZE,
            false,
            false
        },
        0
    };

    if (nvd_init() != 0)
    {
        printf("Error: Could not initialize nvdialog.\n");
        return;
    }


    state.gui_data = gui_init((Vector2){WINDOW_WIDTH, WINDOW_HEIGHT}, &(state.brush.color), &(state.canvas));

    SetTargetFPS(120);
    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);

    while (!WindowShouldClose())
    {
        state.brush.last_pos = state.brush.current_pos;
        state.brush.current_pos = GetMousePosition();

            
        // Screen
        if (!gui_is_click_consumed(state.brush.current_pos, &(state.gui_data)))
        {
            BeginTextureMode(state.canvas.tex);
            canvas_draw_and_connect(&(state.brush), &(state.canvas));

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
                if (state.canvas.is_first_save) 
                { 
                    state.canvas.filename = (char*)malloc(sizeof(char) * 256);
                    memset(state.canvas.filename, 0, sizeof(char) * 256);

                    state.gui_data.current_state = CPAINT_GUI_SAVE_NEW_CANVAS; 
                } 
                else
                {
                    canvas_save(&(state.canvas), state.canvas.filename);
                }

                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
            
        BeginDrawing();
        ClearBackground(BLACK);
        
        canvas_render(&(state.canvas));

        gui_render_all(&(state.gui_data));
        EndDrawing();
    }
    canvas_destroy(&(state.canvas));
    CloseWindow();
}