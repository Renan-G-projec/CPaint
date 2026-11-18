// Ad Maiorem Dei Gloriam!
#ifndef CPAINT_H
#define CPAINT_H

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#include "canvas.h"
#include "gui.h"
 
typedef struct {
    Canvas canvas;
    Brush brush;
    GuiData gui_data;
} CPaintState;

// Creates a local variable representing the state of the program. Can be moved to another struct
void cpaint_start_loop(void);

#endif