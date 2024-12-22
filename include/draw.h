#ifndef DRAW_H
#define DRAW_H

// letter struct
struct Letter {
    int xSteps[10];
    int ySteps[10];
    bool liftPen[10];
    int numSteps;  // number of steps to draw the letter
};




// letterMovements as an external variable to prevent multiple definitions
extern const Letter letterMovements[26];


// Function prototypes for drawing operations
void drawHorizontalLine(int lineLength);
void drawVerticalLine(int lineLength);
void drawLetter(wchar_t letter); // wchar_t is a wide character type that can store unicode characters
void drawSquare(int squareSideLength);
void drawCircle(int r);


#endif // DRAW_H