// Ad Maiorem Dei Gloriam!
#include "filedialogue.h"
#include <raylib.h>

void filedialogue_draw_dialogue(void)
{
    int middle_x = GetScreenWidth() / 2;
    int middle_y = GetScreenHeight() / 2;
    
    const int width = 200;
    const int height = 160;
    
    int pos_x = middle_x - width / 2;
    int pos_y = middle_y - height / 2;

    const char *text = "Save File?";
    const unsigned int text_length = TextLength(text);

    DrawRectangle(pos_x, pos_y, width, height, RAYWHITE);
    DrawText(text, pos_x + 20, pos_y + 20, 16, BLACK);

    // Buttons
    const int button_margin = 20;
    const int button_height = 20;
    const int button_width = (width - 3 * button_margin) / 2;

    const Rectangle exit_button_rec = {
        pos_x + button_margin,
        pos_y + height - button_margin - button_height / 2,
        button_width,
        button_height
    };

    const Rectangle accept_button_rec = {
        pos_x + button_width + button_margin * 2,
        pos_y + height - button_margin - button_height / 2,
        button_width, 
        button_height
    };

    DrawRectangleRec(exit_button_rec, RED); // Exit button
    DrawRectangleRec(accept_button_rec, GREEN); // Accept button

    const int font_size = 10;

    DrawText("NO", exit_button_rec.x + button_margin / 2, exit_button_rec.y + exit_button_rec.height / 2 - font_size / 2, font_size, RAYWHITE);
    DrawText("YES", accept_button_rec.x + button_margin / 2, accept_button_rec.y + accept_button_rec.height / 2 - font_size / 2, font_size, RAYWHITE);
}

FiledialogueInput filedialogue_get_inputs(void)
{
    int middle_x = GetScreenWidth() / 2;
    int middle_y = GetScreenHeight() / 2;
    
    const int width = 200;
    const int height = 160;
    
    int pos_x = middle_x - width / 2;
    int pos_y = middle_y - height / 2;

    // Buttons
    const int button_margin = 20;
    const int button_height = 20;
    const int button_width = (width - 3 * button_margin) / 2;

    const Rectangle exit_button_rec = {
        pos_x + button_margin,
        pos_y + height - button_margin - button_height / 2,
        button_width,
        button_height
    };

    const Rectangle accept_button_rec = {
        pos_x + button_width + button_margin * 2,
        pos_y + height - button_margin - button_height / 2,
        button_width, 
        button_height
    };

    const Vector2 mouse_pos = GetMousePosition();
    const bool pressing = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (pressing && CheckCollisionPointRec(mouse_pos, exit_button_rec)) return FILEDIALOGUE_CLOSE;
    if (pressing && CheckCollisionPointRec(mouse_pos, accept_button_rec)) return FILEDIALOGUE_SAVE;
    return FILEDIALOGUE_NO_INPUT;
}