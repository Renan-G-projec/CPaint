// Ad Maiorme Dei Gloriam!
#include "history.h"
#include "canvas.h"

CanvasHistory history_create(void)
{
    CanvasHistory h;
    h.old_history_initial_image.id = 0;

    h.undo_stack_head = -1;
    h.redo_stack_head = -1;

    h.undo_stack_tail = -1;
    h.redo_stack_tail = -1;

    return h;
}

MouseDrawCommand history_undo(CanvasHistory *history)
{
    if (history_undo_stack_is_empty(history)) return (MouseDrawCommand){NULL, 0};
    
    int undo_stack_top = (history->undo_stack_head + COMMAND_BUFFER_SIZE - 1) % COMMAND_BUFFER_SIZE;
    
    MouseDrawCommand command = history->undo_stack[undo_stack_top];
    
    history->undo_stack_head = undo_stack_top;
    
    // Buffer is empty; should prevent read but not write
    if (history->undo_stack_head == history->undo_stack_tail)
    {
        history->undo_stack_head = -1;
        history->undo_stack_tail = -1;
    }
    
    if (history_redo_stack_is_empty(history)) 
    {
        history->redo_stack_head = 0;
        history->redo_stack_tail = 0;
    }
    else if (history->redo_stack_head == history->redo_stack_tail)
    {
        history->redo_stack_tail = (history->redo_stack_tail + 1) % COMMAND_BUFFER_SIZE; 
    }

    history->redo_stack[history->redo_stack_head] = command;
    history->redo_stack_head = (history->redo_stack_head + 1) % COMMAND_BUFFER_SIZE;

    return command;
}

MouseDrawCommand history_redo(CanvasHistory *history)
{
    if (history_redo_stack_is_empty(history)) return (MouseDrawCommand){NULL, 0};
    
    int redo_stack_top = (history->redo_stack_head + COMMAND_BUFFER_SIZE - 1) % COMMAND_BUFFER_SIZE;
    
    MouseDrawCommand command = history->redo_stack[redo_stack_top];
    
    history->redo_stack_head = redo_stack_top;
    
    // Buffer is empty; should prevent read but not write
    if (history->redo_stack_head == history->redo_stack_tail)
    {
        history->redo_stack_head = -1;
        history->redo_stack_tail = -1;
    }
    
    if (history_undo_stack_is_empty(history)) 
    {
        history->undo_stack_head = 0;
        history->undo_stack_tail = 0;
    }
    else if (history->undo_stack_head == history->undo_stack_tail)
    {
        history->undo_stack_tail = (history->undo_stack_tail + 1) % COMMAND_BUFFER_SIZE; 
    }

    history->undo_stack[history->undo_stack_head] = command;
    history->undo_stack_head = (history->undo_stack_head + 1) % COMMAND_BUFFER_SIZE;

    return command;
}

bool history_undo_stack_is_empty(CanvasHistory *history)
{
    return history->undo_stack_head == -1 && history->undo_stack_tail == -1;
}

bool history_redo_stack_is_empty(CanvasHistory *history)
{
    return history->redo_stack_head == -1 && history->redo_stack_tail == -1;
}

void history_clear_undo_stack(CanvasHistory *history)
{
    if (history_undo_stack_is_empty(history)) return;
    for (int idx = history->undo_stack_tail; idx != history->undo_stack_head; idx = (idx + 1) % COMMAND_BUFFER_SIZE)
    {
        if (!history->undo_stack[idx].mouse_logs) continue;
        free(history->undo_stack[idx].mouse_logs);
    }

    history->undo_stack_head = -1;
    history->undo_stack_tail = -1;
}

void history_clear_redo_stack(CanvasHistory *history)
{
    if (history_undo_stack_is_empty(history)) return;

    for (int idx = history->redo_stack_tail; idx != history->redo_stack_head; idx = (idx + 1) % COMMAND_BUFFER_SIZE)
    {
        if (!history->redo_stack[idx].mouse_logs) continue;
        free(history->redo_stack[idx].mouse_logs);
    }

    history->redo_stack_head = -1;
    history->redo_stack_tail = -1;
}

MouseDrawCommand *history_get_last_mouse_draw_command(CanvasHistory *history)
{
    if (history_undo_stack_is_empty(history)) return NULL;
    return history->undo_stack + (history->undo_stack_head + COMMAND_BUFFER_SIZE - 1) % COMMAND_BUFFER_SIZE;
}

void history_destroy(CanvasHistory *history)
{
    history_clear_undo_stack(history);   
    history_clear_redo_stack(history);
}

MouseDrawCommand *history_create_mouse_draw_command(CanvasHistory* history, float brush_size, Color brush_color)
{
    if (history_undo_stack_is_empty(history)) 
    {
        history->undo_stack_head = 0;
        history->undo_stack_tail = 0;
    }
    else if (history->undo_stack_head == history->undo_stack_tail)
    {
        history->undo_stack_tail++;
    }
    
    const MouseDrawCommand mouse_draw_command = (MouseDrawCommand){malloc(MOUSE_BUFFER_SIZE * sizeof(Vector2)), (size_t)0, (size_t)MOUSE_BUFFER_SIZE, brush_color, brush_size};

    history->undo_stack[history->undo_stack_head] = mouse_draw_command;
    MouseDrawCommand *mouse_draw_command_address = history->undo_stack + history->undo_stack_head;

    history->undo_stack_head++;
    
    history->undo_stack_head %= COMMAND_BUFFER_SIZE;
    history->undo_stack_tail %= COMMAND_BUFFER_SIZE;
    
    return mouse_draw_command_address;
}

void history_log_mouse_position(MouseDrawCommand* command, const Vector2 mouse_position)
{
    if (!command) return;
    const Vector2 command_mouse_pos = command->mouse_logs[command->num_of_logs];

    if ((int)command_mouse_pos.x == (int)mouse_position.x && (int)command_mouse_pos.y == (int)mouse_position.y)
    {
        printf("Mouse is on same position!\n");
        return;
    }

    if (command->num_of_logs + 1 >= command->log_capacity)
    {
        command->log_capacity *= 2;
        command->mouse_logs = realloc(command->mouse_logs, command->log_capacity * sizeof(Vector2));
        if (command->mouse_logs == NULL) 
        {
            exit(1);
        }
    }

    command->mouse_logs[command->num_of_logs++] = mouse_position;
}

void history_save_snapshot(CanvasHistory *history, Texture2D snapshot)
{
    if (history->old_history_initial_image.id > 0)
    {
        UnloadTexture(history->old_history_initial_image);
    }
    
    history->old_history_initial_image = snapshot;
}