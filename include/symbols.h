#ifndef SYMBOLS_H
#define SYMBOLS_H

// letter struct
struct Letter {
    int xSteps[10];
    int ySteps[10];
    int numSteps;  // number of steps to draw the letter
};

// letterMovements as an external variable to prevent multiple definitions
extern const Letter letterMovements[26];

#endif  // SYMBOLS_H