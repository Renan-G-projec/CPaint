// Ad Maiorme Dei Gloriam!
#include "history.h"

EditorHistory history_create(void)
{
    EditorHistory h;

    h.undo_stack_head = 0;
    h.redo_stack_head = 0;

    h.undo_stack_tail = -1;
    h.redo_stack_tail = -1;

    return h;
}

MouseDrawCommand history_undo(EditorHistory* history)
{

    if (history->undo_stack_head < history->undo_stack_tail) return (MouseDrawCommand){NULL, 0};

    MouseDrawCommand command = history->undo_stack[history->undo_stack_head];
    if (--history->undo_stack_head < 0)
    {
        history->undo_stack_head = COMMAND_BUFFER_SIZE - 1;
    }

    if (++history->redo_stack_head >= history->redo_stack_tail)
    {
        history->redo_stack_tail++;

        history->redo_stack_head %= COMMAND_BUFFER_SIZE;
        history->redo_stack_tail %= COMMAND_BUFFER_SIZE;
    }

    history->redo_stack[history->redo_stack_head] = command;
    
    return command;
}

MouseDrawCommand history_redo(EditorHistory* history)
{
    if (history->redo_stack_head < history->redo_stack_tail) return (MouseDrawCommand){NULL, 0};

    MouseDrawCommand command = history->redo_stack[history->redo_stack_head];
    if (--history->redo_stack_head < 0)
    {
        history->redo_stack_head = COMMAND_BUFFER_SIZE - 1;
    }

    if (++history->undo_stack_head >= history->undo_stack_tail)
    {
        history->undo_stack_tail++;

        history->undo_stack_head %= COMMAND_BUFFER_SIZE;
        history->undo_stack_tail %= COMMAND_BUFFER_SIZE;
    }

    history->undo_stack[history->undo_stack_head] = command;
    
    return command;
}

MouseDrawCommand* history_create_mouse_draw_command(EditorHistory* history)
{
    if (++history->undo_stack_head >= history->undo_stack_tail)
    {
        history->undo_stack_tail++;

        history->undo_stack_head %= COMMAND_BUFFER_SIZE;
        history->undo_stack_tail %= COMMAND_BUFFER_SIZE;
    }

    history->undo_stack[history->undo_stack_head] = (MouseDrawCommand){NULL, 0};
    return history->undo_stack + history->undo_stack_head;
}