// Ad Maiorem Dei Gloriam!
#ifndef FILEDIALOGUE_H
#define FILEDIALOGUE_H

typedef enum {
    FILEDIALOGUE_NO_INPUT,
    FILEDIALOGUE_CLOSE,  
    FILEDIALOGUE_SAVE,
} FiledialogueInput;

FiledialogueInput filedialogue_draw_and_get_inputs(char *filename);

#endif