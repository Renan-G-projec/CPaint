// Ad Maiorem Dei Gloriam!
#include <string.h>
#include <stdio.h>
#include "gui.h"
#include "raygui.h"

GuiData gui_init(Vector2 screen_size, Color *current_color)
{
    GuiData d;

    d.current_color = current_color;

    d.color_picker_rec = (Rectangle){20, screen_size.y - 140, 120, 120};
    d.color_picker_toggle_rec = (Rectangle){20, screen_size.y - 40, 100, 20};

    d.save_new_canvas_rec = (Rectangle){screen_size.x / 2 - 200, screen_size.y / 2 - 200, 400, 400};
    d.save_new_canvas_input_rec = (Rectangle){d.save_new_canvas_rec.x + 20, (d.save_new_canvas_rec.height / 2) * 2, 360, 40};

    d.current_state = CPAINT_GUI_FREE;
    d.shall_save = false;

    d.filename_buffer = NULL;

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

    if (data->current_state == CPAINT_GUI_SAVE_NEW_CANVAS)
    {
        int btn = 0;
        GuiMessageBox(data->save_new_canvas_rec, "Save canvas", "Save Canvas\nInput the directory and the filename the file will be saved on.", "Close;Save", &btn);
        GuiTextBox(data->save_new_canvas_input_rec, data->filename_buffer, 255, true);
        if (btn == 1) data->current_state = CPAINT_GUI_FREE;
        if (btn == 2)
        { 
            data->shall_save = true;
            data->current_state = CPAINT_GUI_FREE;
        }
    }
}

void gui_render_color_picker(Rectangle rect, Color *dest)
{
    GuiColorPicker(rect, "Color picker", dest);
}