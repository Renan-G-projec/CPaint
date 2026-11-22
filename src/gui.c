// Ad Maiorem Dei Gloriam!
#include <string.h>
#include <stdio.h>
#include "gui.h"
#include "raygui.h"

GuiData gui_init(Vector2 screen_size, Color *current_color, Canvas *current_canvas)
{
    GuiData d;

    d.current_color = current_color;
    d.current_canvas = current_canvas;

    d.color_picker_rec = (Rectangle){20, screen_size.y - 140, 120, 120};
    d.color_picker_toggle_rec = (Rectangle){20, screen_size.y - 40, 100, 20};

    d.save_new_canvas_rec = (Rectangle){screen_size.x / 2 - 200, screen_size.y / 2 - 200, 400, 400};
    d.save_new_canvas_input_rec = (Rectangle){d.save_new_canvas_rec.x + 20, (d.save_new_canvas_rec.height / 2) * 2, 360, 40};

    d.current_state = CPAINT_GUI_FREE;
    d.mouse_clicked_gui = false;

    d.on_error = false;
    
    return d;
}

bool gui_is_click_consumed(Vector2 mouse_pos, GuiData *data) { 
    if (data->mouse_clicked_gui && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) return true;
    data->mouse_clicked_gui = false;

    // MAIN SCREEN BUTTONS
    if (data->current_state == CPAINT_GUI_FREE)
    {
        // COLOR PICKER
        if (CheckCollisionPointRec(mouse_pos, data->color_picker_toggle_rec)) return true;
    }

    if (data->current_state == CPAINT_GUI_CHANGING_COLOR)
    {
        return true;
    }
    return false;
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

        if (!data->mouse_clicked_gui && !color_changed && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(GetMousePosition(), data->color_picker_rec))
        {
            data->mouse_clicked_gui = true;
            data->current_state = CPAINT_GUI_FREE;
        }
    }

    if (data->current_state == CPAINT_GUI_SAVE_NEW_CANVAS)
    {
        int btn = 0;
        GuiMessageBox(data->save_new_canvas_rec, "Save canvas", "Save Canvas\nInput the directory and the filename the file will be saved on.", "Close;Save", &btn);
        GuiTextBox(data->save_new_canvas_input_rec, data->current_canvas->filename, 255, true);
        if (btn != 0) data->mouse_clicked_gui = true;
        if (btn == 1) data->current_state = CPAINT_GUI_FREE;
        if (btn == 2)
        { 
            bool success = save_canvas_to_file(data->current_canvas, data->current_canvas->filename);
            if (success)
            {
                data->current_canvas->is_first_save = false;
                data->current_state = CPAINT_GUI_FREE;
            }
            else
            {
                data->on_error = true;
                strncpy(data->error_message, "Error: Could not save or open file", 128);
            }
        }
    }

    gui_render_error(data);
}

void gui_render_color_picker(Rectangle rect, Color *dest)
{
    GuiColorPicker(rect, "Color picker", dest);
}

void gui_render_error(GuiData *data)
{
    if (!data->on_error) return;
    if (GuiWindowBox(data->save_new_canvas_rec, data->error_message))
    {
        data->on_error = false;
    }
}