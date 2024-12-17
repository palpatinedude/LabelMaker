#include "draw.h"
#include "motor.h"
#include "pins.h"
#include "movement.h"
/*
// movement of the letters
const Letter letterMovements[26] = {
    {{0, 4250,-4250,200,0}, {0, 20,20,0,-200}, 5},  // 'A'
    {{0, 50, 100}, {0, 100, 200}, 3},  // 'B'
    //others
};
*/
// movement of the letters
const Letter letterMovements[26] = {
    {{0, 2500,2500,2500,-2500,-2500,-2500,3000,0}, {0, 45,45,45,45,45,45,0,-157}, 10},  // 'A'
    {{0, 50, 100}, {0, 100, 200}, 3},  // 'B'
    //others
};


//  draw the letter based on input
void drawLetter(char letter) {
    Serial.println("Starting letter drawing...");

    if (letter >= 'A' && letter <= 'Z') {
        int index = letter - 'A';  // convert letter to array index (0 for 'A', 1 for 'B', etc.)
        const Letter& movements = letterMovements[index];
     
        penControl(true);  // lift the pen initially
        motorX.moveSteps(movements.xSteps[0]);  // move from start position
        motorY.moveSteps(movements.ySteps[0]);
        penControl(false);   // lower the pen to draw
        for (int i = 1; i < movements.numSteps; i++) {
            if (i == 7){
                penControl(true);  // lift the pen after drawing
            }
            if (i == 8){
                penControl(false);  // lower the pen to draw
            }
            
            motorX.moveSteps(movements.xSteps[i]);  // move according to x and y steps
            motorY.moveSteps(movements.ySteps[i]);
            while (motorX.getStepper().isRunning() || motorY.getStepper().isRunning()) {
                motorX.run();
                motorY.run();
            }
        }
        penControl(false);  // lift the pen after drawing
    }
}


void drawHorizontalLine(int lineLength) {
    Serial.println("Starting vertical line..."); 
    penControl(false); 
    // draw the upper horizontal line
    delay(1000);
    motorY.moveSteps(lineLength);  

    while (motorY.getStepper().isRunning()) {
        motorY.run();  
        currentPositionY = motorY.getStepper().currentPosition();
    }
    penControl(true);  
    Serial.println("Vertical line complete.");
}

void drawVerticalLine(int lineLength) {
    Serial.println("Starting vertical line..."); 
    penControl(false); 
  
    delay(1000);
    motorX.moveSteps(lineLength);  
    while (motorX.getStepper().isRunning()) {
        motorX.run();  
        currentPositionX = motorX.getStepper().currentPosition();
    }

    penControl(true);  
    Serial.println("Vertical line complete.");
}



void drawSquare(int squareSideLength) {
    // four sides of the square

    drawHorizontalLine(235*squareSideLength); 
    delay(1000);
    drawVerticalLine(4250*squareSideLength); 
    delay(1000);
    drawHorizontalLine(-235*squareSideLength);
    delay(1000);
    drawVerticalLine(-4250*squareSideLength);
    delay(1000);
}

