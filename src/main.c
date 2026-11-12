// Ad Maiorem Dei Gloriam!
#include <stdio.h>
#include <raylib.h>

#define WINDOW_WIDTH 160 * 6
#define WINDOW_HEIGHT 90 * 6

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPaint");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawCircle(400, 400, 9, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;    
}