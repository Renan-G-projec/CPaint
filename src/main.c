// Ad Maiorem Dei Gloriam!
#include "cpaint.h"

#include "viewport.h"
#include "canvas.h"

int main(void)
{
    //cpaint_start_loop()

    InitWindow(1280, 720, "Test");

    Canvas canvas = {
        LoadRenderTexture(100, 100),
        history_buffer_create(),
        history_buffer_create(),
        false,
        {0, 0},
        NULL,
        true,
    };

    Viewport viewport = viewport_init((Rectangle){140.0f, 60.0f, 1000.0f, 600.0f}, &canvas);

    BeginTextureMode(canvas.tex);

    ClearBackground(PURPLE);

    EndTextureMode();
    SetTargetFPS(60);
    history_buffer_append(&(canvas.undo_buffer), canvas_take_snapshot(&canvas));
    while (!WindowShouldClose())
    {
        viewport_update(&viewport);
        viewport_render_internal(&viewport);

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            canvas_undo(&canvas);
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
        {
            canvas_redo(&canvas);
        }
        BeginDrawing();

        viewport_render(&viewport);

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
