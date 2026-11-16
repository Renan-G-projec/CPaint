// Ad Maiorem Dei Gloriam!
#include "filedialogue.h"
#include <raygui.h>
#include <raylib.h>

bool secret = true;

FiledialogueInput filedialogue_draw_and_get_inputs(char* filename)
{
    FiledialogueInput input = 0;

    const Rectangle message_rect = {
        (int)(GetScreenWidth() / 2) - 100,
        (int)(GetScreenHeight() / 2) - 100,
        200,
        200
    };

    const Rectangle text_input = {
        message_rect.x + 20,
        message_rect.y + message_rect.height - 80,
        message_rect.width - 40,
        20
    };

    GuiMessageBox(message_rect, "Save File", "Put the text below \nto export the image.", "Close;Save", (int*)&input);
    GuiTextBox(text_input, filename, 256, true);
    
    return input;
}
