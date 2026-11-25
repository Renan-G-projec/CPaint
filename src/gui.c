// Ad Maiorem Dei Gloriam!
#include <string.h>
#include <stdio.h>
#include "gui.h"
#include "raygui.h"

GuiData gui_init(Color *current_color, Canvas *current_canvas)
{
    GuiData d;

    d.current_color = current_color;
    d.current_canvas = current_canvas;

    d.is_picking_color = false;
    
    d.on_error = false;
    
    return d;
}

void gui_update(GuiData *data)
{
    if (data->is_picking_color)
    {
        GuiUnlock();
        DrawRectangle(0.0f, 0.0f, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 100});
        
        Color current_color = *data->current_color;
        GuiColorPicker(GUI_COLOR_PICKER_RECT, "ColorPicker", data->current_color);
        bool color_changed =    current_color.r != data->current_color->r 
                             || current_color.b != data->current_color->b
                             || current_color.g != data->current_color->g
                             || current_color.a != data->current_color->a;
    
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !color_changed) data->is_picking_color = false;
    
        GuiLock();
    }
    if (GuiButton(GUI_CHANGE_COLOR_BUTTON_RECT, "Change Color"))
    {
        data->is_picking_color = true;
    }
GuiUnlock();
}
