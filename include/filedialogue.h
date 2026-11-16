// Ad Maiorem Dei Gloriam!
#ifndef FILEDIALOGUE_H
#define FILEDIALOGUE_H

typedef enum {
    FILEDIALOGUE_NO_INPUT,
    FILEDIALOGUE_SAVE,
    FILEDIALOGUE_CLOSE  
} FiledialogueInput;

void filedialogue_draw_dialogue(void);
FiledialogueInput filedialogue_get_inputs(void);

#endif