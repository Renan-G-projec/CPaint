// Ad Maiorem Dei Gloriam!

#include "nvdialog.h"
#include "viewport.h"
#include "canvas.h"
#include "dynamic_string.h"
#include "gui.h"

#define CTRL_KEY(key) ((IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyDown(KEY_LEFT_CONTROL)) && IsKeyPressed(key))

int main(void)
{
    // Nvdialog for saving files and opening those
    if (nvd_init() != 0)
    {
        puts("Error: Could not initialize nvdialog.\n");
        return 1;
    }

    InitWindow(1280, 720, "Test");

    Canvas canvas = {
        LoadRenderTexture(100, 100),
        history_buffer_create(),
        history_buffer_create(),
        false,
        {0, 0},
        true,
        dynamic_string_new(512)
    };

    if (!canvas.filename.buffer)
    {
        puts("Error: Could not allocate memory to filename.");
        return 1;
    }
    

    Color color = WHITE;
    GuiData gui = gui_init(&color, &canvas);

    Viewport viewport = viewport_init((Rectangle){140.0f, 60.0f, 1000.0f, 600.0f}, &canvas);

    BeginTextureMode(canvas.tex);

    ClearBackground(PURPLE);

    EndTextureMode();
    SetTargetFPS(60);
    history_buffer_append(&(canvas.undo_buffer), canvas_take_snapshot(&canvas));

    while (!WindowShouldClose())
    {
        if (!gui.is_picking_color)
        {
            viewport_update(&viewport, color);
            viewport_render_internal(&viewport);
        }
            
        
        if (CTRL_KEY(KEY_Z))
        {
            canvas_undo(&canvas);
        }
        else if (CTRL_KEY(KEY_Y))
        {
            canvas_redo(&canvas);
        }
        BeginDrawing();

        ClearBackground(BLACK);
        viewport_render(&viewport);
        gui_update(&gui);

        EndDrawing();
    }
    
    CloseWindow();
    canvas_destroy(&canvas);
    return 0;
}
