// Ad Maiorem Dei Gloriam!
#ifndef HISTORY_BUFFER_H
#define HISTORY_BUFFER_H

#include <stdint.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

#define HISTORY_BUFFER_SIZE 10

typedef uint8_t history_size_t;
typedef uint8_t history_head_t;
typedef uint8_t history_tail_t;

typedef struct
{
    Texture2D snapshots[HISTORY_BUFFER_SIZE];
    history_size_t size;
    history_head_t head;
    history_tail_t tail;
} HistoryBuffer;


HistoryBuffer history_buffer_create(void);
Texture2D *history_buffer_append(HistoryBuffer *, Texture2D);
Texture2D *history_buffer_move(HistoryBuffer *origin, HistoryBuffer *dest);
Texture2D *history_buffer_top(HistoryBuffer *);
void history_buffer_clear(HistoryBuffer *);

#endif
