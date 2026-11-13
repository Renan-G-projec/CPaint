// Ad Maiorme Dei Gloriam!
#include "history.h"

EditorHistory history_create(void)
{
    EditorHistory h;

    h.undo_stack_head = -1;
    h.redo_stack_head = -1;

    h.undo_stack_tail = -1;
    h.redo_stack_tail = -1;

    return h;
}

MouseDrawCommand history_undo(EditorHistory *history)
{
    if (history_undo_stack_is_empty(history)) return (MouseDrawCommand){NULL, 0};
    if (history_redo_stack_is_empty(history)) 
    {
        history->redo_stack_head = 0;
        history->redo_stack_tail = 0;
    }

    MouseDrawCommand command = history->undo_stack[history->undo_stack_head];
    if (--history->undo_stack_head < 0)
    {
        history->undo_stack_head = COMMAND_BUFFER_SIZE - 1;
    }

    if (++history->redo_stack_head == history->redo_stack_tail)
    {
        free(history->redo_stack[history->redo_stack_head].mouse_logs);
        history->redo_stack_tail++;

        history->redo_stack_head %= COMMAND_BUFFER_SIZE;
        history->redo_stack_tail %= COMMAND_BUFFER_SIZE;
    }

    history->redo_stack[history->redo_stack_head] = command;
    
    return command;
}

MouseDrawCommand history_redo(EditorHistory *history)
{
    if (history_redo_stack_is_empty(history)) return (MouseDrawCommand){NULL, 0};
    if (history_undo_stack_is_empty(history)) 
    {
        history->undo_stack_head = 0;
        history->undo_stack_tail = 0;
    }

    MouseDrawCommand command = history->redo_stack[history->redo_stack_head];
    if (--history->redo_stack_head < 0)
    {
        history->redo_stack_head = COMMAND_BUFFER_SIZE - 1;
    }

    if (++history->undo_stack_head == history->undo_stack_tail)
    {
        free(history->undo_stack[history->undo_stack_head].mouse_logs);
        history->undo_stack_tail++;

        history->undo_stack_head %= COMMAND_BUFFER_SIZE;
        history->undo_stack_tail %= COMMAND_BUFFER_SIZE;
    }
    
    history->undo_stack[history->undo_stack_head] = command;
    
    return command;
}

bool history_undo_stack_is_empty(EditorHistory *history)
{
    return history->undo_stack_head == -1 && history->undo_stack_tail == -1;
}

bool history_redo_stack_is_empty(EditorHistory *history)
{
    return history->redo_stack_head == -1 && history->redo_stack_tail == -1;
}

MouseDrawCommand* history_create_mouse_draw_command(EditorHistory* history)
{
    if (history_undo_stack_is_empty(history)) 
    {
        history->undo_stack_head = 0;
        history->undo_stack_tail = 0;
    }

    history->undo_stack_head++;

    history->undo_stack_head %= COMMAND_BUFFER_SIZE;
    history->undo_stack_tail %= COMMAND_BUFFER_SIZE;
    
    if (history->undo_stack_head == history->undo_stack_tail)
    {
        history->undo_stack_tail++;
    }
    
    history->undo_stack[history->undo_stack_head] = (MouseDrawCommand){malloc(MOUSE_BUFFER_SIZE * sizeof(Vector2)), (size_t)0, (size_t)MOUSE_BUFFER_SIZE};
    
    return history->undo_stack + history->undo_stack_head;
}

void history_log_mouse_position(MouseDrawCommand* command, const Vector2 mouse_position)
{
    if (!command) return;

    if (command->num_of_logs + 1 >= command->log_capacity)
    {
        command->log_capacity *= 2;
        command->mouse_logs = realloc((void*)command->mouse_logs, command->log_capacity);
        if (command->mouse_logs == NULL) 
        {
            exit(1);
        }
    }

    command->mouse_logs[command->num_of_logs++] = mouse_position;
}