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
        history_create(),
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

    while (!WindowShouldClose())
    {
        viewport_update(&viewport);
        viewport_render_internal(&viewport);

        BeginDrawing();

        viewport_render(&viewport);

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
