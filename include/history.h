// Ad Maiorem Dei Gloriam!
#include <raylib.h>
#include <stdlib.h>

#define COMMAND_BUFFER_SIZE 32

typedef struct
{
    Vector2 *mouse_logs;
    size_t num_of_logs;
} MouseDrawCommand;

// Editor History should not realllocate each time so a circular buffer works better. 32 is even a overkill for here

typedef struct
{
    MouseDrawCommand undo_stack[COMMAND_BUFFER_SIZE];
    MouseDrawCommand redo_stack[COMMAND_BUFFER_SIZE];

    int undo_stack_head;
    int redo_stack_head;

    int undo_stack_tail;
    int redo_stack_tail;
} EditorHistory;

EditorHistory history_create(void);
MouseDrawCommand history_undo(EditorHistory*);
MouseDrawCommand history_redo(EditorHistory*);

MouseDrawCommand* history_create_mouse_draw_command(EditorHistory*);
void history_log_mouse_position(MouseDrawCommand*, const Vector2 mouse_position);

