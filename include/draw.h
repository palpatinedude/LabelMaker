#ifndef DRAW_H
#define DRAW_H

// letter struct
struct Letter {
    int xSteps[10];
    int ySteps[10];
    int numSteps;  // number of steps to draw the letter
};

// letterMovements as an external variable to prevent multiple definitions
extern const Letter letterMovements[26];


// Function prototypes for drawing operations
void drawHorizontalLine(int lineLength);
void drawVerticalLine(int lineLength);
void drawLetter(char letter);
void drawSquare(int squareSideLength);


#endif // DRAW_H