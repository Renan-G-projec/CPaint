// Ad Maiorme Dei Gloriam!
#include "history.h"
#include "canvas.h"

CanvasHistory history_create(void)
{
    CanvasHistory h;
    h.old_history_stack = malloc(sizeof(MouseDrawCommand) * MOUSE_BUFFER_SIZE);
    h.old_history_stack_capacity = MOUSE_BUFFER_SIZE;
    h.old_history_stack_size = 0;

    if (!h.old_history_stack)
    {
        exit(1);
    }

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
        history_push_to_old_history(history, history->redo_stack[history->redo_stack_tail]);
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
        history_push_to_old_history(history, history->undo_stack[history->undo_stack_tail]);

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
    return history->undo_stack + (history->undo_stack_head + COMMAND_BUFFER_SIZE - 1) % COMMAND_BUFFER_SIZE;
}

void history_destroy(CanvasHistory *history)
{
    history_clear_undo_stack(history);   
    history_clear_redo_stack(history);
    history_clear_old_history(history);
}

MouseDrawCommand *history_create_mouse_draw_command(CanvasHistory* history, float brush_size)
{
    if (history_undo_stack_is_empty(history)) 
    {
        history->undo_stack_head = 0;
        history->undo_stack_tail = 0;
    }
    else if (history->undo_stack_head == history->undo_stack_tail)
    {
        history_push_to_old_history(history, history->undo_stack[history->undo_stack_tail]);
        history->undo_stack_tail++;
    }
    
    const MouseDrawCommand mouse_draw_command = (MouseDrawCommand){malloc(MOUSE_BUFFER_SIZE * sizeof(Vector2)), (size_t)0, (size_t)MOUSE_BUFFER_SIZE, brush_size};

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
    // The old command table is not needed anymore.
    for (size_t deletion_index = 0; deletion_index < history->old_history_stack_size; ++deletion_index)
    {
        if (history->old_history_stack[deletion_index].mouse_logs) free(history->old_history_stack[deletion_index].mouse_logs);
    }
    history->old_history_stack_size = 0;

    history->old_history_initial_image = snapshot;
}

void history_push_to_old_history(CanvasHistory *history, MouseDrawCommand cmd)
{
    history->old_history_stack_size++;
    if (history->old_history_stack_size >= history->old_history_stack_capacity)
    {
        history->old_history_stack_capacity *= 2;
        history->old_history_stack = realloc(history->old_history_stack, sizeof(MouseDrawCommand) * history->old_history_stack_capacity);
        if (!history->old_history_stack)
        {
            exit(1);
        }
    }

    history->old_history_stack[history->old_history_stack_size] = cmd;
}

void history_clear_old_history(CanvasHistory *history)
{
    for (size_t i = 0; i < history->old_history_stack_size; ++i)
    {
        Vector2 *mouse_logs = history->old_history_stack[i].mouse_logs;
        if (mouse_logs) free(mouse_logs);
    }
    free(history->old_history_stack);
}
