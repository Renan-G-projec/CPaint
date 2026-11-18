// Ad Maiorem Dei Gloriam!
#include "gui.h"
#include "raygui.h"

GuiData gui_init(Vector2 screen_size, Color *current_color)
{
    GuiData d;

    d.current_color = current_color;
    d.current_state = CPAINT_GUI_FREE;
    d.color_picker_rec = (Rectangle){20, screen_size.y - 140, 120, 120};
    d.color_picker_toggle_rec = (Rectangle){20, screen_size.y - 40, 100, 20};
    return d;
}

bool gui_is_click_consumed(Vector2 mouse_pos, GuiData *data) { 
    return data->current_state != CPAINT_GUI_FREE;
}

void gui_render_all(GuiData *data)
{
    
    bool color_picker_toggled = GuiButton(data->color_picker_toggle_rec, "Pick Color");
    if (color_picker_toggled) data->current_state = CPAINT_GUI_CHANGING_COLOR;

    if (data->current_state == CPAINT_GUI_CHANGING_COLOR)
    {
        Color old_color = *data->current_color;
        gui_render_color_picker(data->color_picker_rec, data->current_color);

        bool color_changed = 
            old_color.r != data->current_color->r 
            || old_color.g != data->current_color->g 
            || old_color.b != data->current_color->b 
            || old_color.a != data->current_color->a;

        if (!color_changed && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(GetMousePosition(), data->color_picker_rec))
        {
            data->current_state = CPAINT_GUI_FREE;
        }
    }
}

void gui_render_color_picker(Rectangle rect, Color *dest)
{
    GuiColorPicker(rect, "Color picker", dest);
}