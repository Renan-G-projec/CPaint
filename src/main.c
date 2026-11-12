// Ad Maiorem Dei Gloriam!
#include <stdio.h>
#include <raylib.h>

#define WINDOW_WIDTH 160 * 6
#define WINDOW_HEIGHT 90 * 6

void draw_canvas(RenderTexture2D *canvas, Vector2 position)
{
        BeginDrawing();
        DrawTextureRec(canvas->texture, (Rectangle){0, 0, canvas->texture.width, -canvas->texture.height}, position, WHITE);
        EndDrawing();
}

bool save_canvas_to_file(RenderTexture2D *canvas, const char *filepath)
{
    Image img = LoadImageFromTexture(canvas->texture);
    return ExportImage(img, filepath);
}

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPaint");

    RenderTexture2D canvas = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!WindowShouldClose())
    {
        
        BeginTextureMode(canvas);        
        Vector2 mousePos = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawCircle(mousePos.x, mousePos.y, 9, RAYWHITE);
        }
        
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            ClearBackground(BLACK);
        }
        EndTextureMode();

        draw_canvas(&canvas, (Vector2){0, 0});
    }

    CloseWindow();
    return 0;    
}