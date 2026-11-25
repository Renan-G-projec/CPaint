// Ad Maiorme Dei Gloriam!
#include "history_buffer.h"
#include "canvas.h"

HistoryBuffer history_buffer_create(void)
{
    HistoryBuffer h;

    h.size = 0;
    h.head = 0;
    h.tail = 0;

    return h;
}

Texture2D *history_buffer_append(HistoryBuffer *history_buf, Texture2D snapshot)
{
    if (history_buf->size >= HISTORY_BUFFER_SIZE)
    {
        UnloadTexture(history_buf->snapshots[history_buf->tail]);

        history_buf->tail = (history_buf->tail + 1) % HISTORY_BUFFER_SIZE;
    }
    else
    {
        history_buf->size++;
    }

    history_buf->snapshots[history_buf->head] = snapshot;
    Texture* texture_on_buffer = history_buf->snapshots + history_buf->head;

    history_buf->head = (history_buf->head + 1) % HISTORY_BUFFER_SIZE;
    return texture_on_buffer;
}

Texture2D *history_buffer_move(HistoryBuffer *origin, HistoryBuffer *dest)
{
    if (origin->size == 0) return NULL;

    origin->head = (origin->head + HISTORY_BUFFER_SIZE - 1) % HISTORY_BUFFER_SIZE;
    origin->size--;
    return history_buffer_append(dest, origin->snapshots[origin->head]);
}

Texture2D *history_buffer_top(HistoryBuffer *history_buf)
{
    if (history_buf->size == 0) return NULL;
    return history_buf->snapshots + (history_buf->head + HISTORY_BUFFER_SIZE - 1) % HISTORY_BUFFER_SIZE;
}

void history_buffer_clear(HistoryBuffer *history_buf)
{
    for (history_tail_t i = history_buf->tail; i != history_buf->head; ++i % HISTORY_BUFFER_SIZE)
    {
        UnloadTexture(history_buf->snapshots[i]);
    }

    history_buf->size = 0;
    history_buf->head = 0;
    history_buf->tail = 0;
}