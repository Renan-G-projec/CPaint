// Ad Maiorem Dei Gloriam!
#ifndef HISTORY_H
#define HISTORY_H

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "history.h"

#define COMMAND_BUFFER_SIZE 32
#define MOUSE_BUFFER_SIZE 1024

typedef struct
{
    Vector2 *mouse_logs;
    size_t num_of_logs;
    size_t log_capacity;
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
bool history_undo_stack_is_empty(EditorHistory*);
bool history_redo_stack_is_empty(EditorHistory*);
MouseDrawCommand *history_get_last_mouse_draw_command(EditorHistory*);
void history_destroy(EditorHistory*);

MouseDrawCommand* history_create_mouse_draw_command(EditorHistory*);
void history_log_mouse_position(MouseDrawCommand*, const Vector2 mouse_position);

#endif