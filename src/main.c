// Ad Maiorem Dei Gloriam!
#include <stdio.h>
#include <raylib.h>

#define WINDOW_WIDTH 160 * 6
#define WINDOW_HEIGHT 90 * 6

#define DEFAULT_BRUSH_SIZE 10.0f
#define BRUSH_ADJUSTMENT_SIZE 1.0f
#define BRUSH_MINIMUM_SIZE 1.0f

void draw_canvas(RenderTexture2D *canvas, Vector2 position)
{
    DrawTextureRec(canvas->texture, (Rectangle){0, 0, canvas->texture.width, -canvas->texture.height}, position, WHITE);
}

void draw_brush_target(float brush_size)
{
    Vector2 mouse_pos = GetMousePosition();

    DrawCircle(mouse_pos.x, mouse_pos.y, brush_size, RAYWHITE);
}

bool save_canvas_to_file(RenderTexture2D *canvas, const char *filepath)
{
    Image img = LoadImageFromTexture(canvas->texture);
    return ExportImage(img, filepath);
}

void handle_brush_size_input(float *dest)
{
    if (IsKeyPressed(KEY_EQUAL))
    {
        *dest += BRUSH_ADJUSTMENT_SIZE; 
    }
    if (IsKeyPressed(KEY_MINUS))
    {
        *dest -= BRUSH_ADJUSTMENT_SIZE;
        if (*dest < BRUSH_MINIMUM_SIZE) *dest = BRUSH_MINIMUM_SIZE;                 
    }
}

void handle_brush_draw_input(float brush_size) 
{
    Vector2 mouse_pos = GetMousePosition();


    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        DrawCircle(mouse_pos.x, mouse_pos.y, brush_size, RAYWHITE);
    }
    
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        ClearBackground(BLACK);
    }
}

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPaint");

    RenderTexture2D canvas = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

    float brush_size = DEFAULT_BRUSH_SIZE;

    while (!WindowShouldClose())
    {

        // Canvas
        BeginTextureMode(canvas);        
            handle_brush_draw_input(brush_size);
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