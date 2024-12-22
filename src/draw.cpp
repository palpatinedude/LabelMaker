#include "draw.h"
#include "motor.h"
#include "pins.h"
#include "movement.h"
#include <map>


// movement of the letters
const Letter letterMovements[26] = {
    {{0, 2500,2500,2500,-2500,-2500,-2500,3000,0}, {0, 45,45,45,45,45,45,0,-157},{1,0,0,0,0,0,0,1,0}, 9},  // 'A'
    {{0, 5500, 350,350,350,350,-350,-350,-350,-350}, {0, 0, 45,45,45,45,34,34,34,34}, 10},  // 'B'
    {{0,4550,0},{0,0,215},{1,0,0},3},  // 'Γ'
    {{0, 4350,0,-2175,0}, {0, 0,200,-200},{0,0,0,1} , 6},  // 'Δ'
    {{0, 4550,0,0,-2275,0,0,-2275,0}, {0, 0,200,-230,0,200,-200,0,200},{0,0,0,1,1,0,1,1,0} , 9},  // 'Ε'
    {{0, 4000, -4000, 4000, -4000}, {0, 0, 45, 45, 0}, 5},  // 'Ζ'
    {{0, 0, 4000, 0, 0}, {0, 45, 0, -45, 0}, 5},  // 'Η'
    {{0, 2500, 2500, -2500, -2500, 0, 0, 2500, -2500}, {0, 45, 45, 45, 45, 0, 45, 45, 45},  9}, //'Θ'
    {{0, 4550},  {0, 0},{1,0} ,2}, // 'Ι'
    {{0, 0, 3500, 0, 3500}, {0, 45, -45, 45, 0}, 5}, // 'Κ'
    {{0, 2500, 2500, -2500, -2500, 0}, {0, 45, 45, 45, 45, 0}, 6}, //'Λ'
    {{0, 0, 4000, 0, 4000}, {0, 45, 0, -45, 0},  5}, // 'Μ'
    {{0, 0, 4000, 0},  {0, 45, 45, 0},  4}, // 'Ν'
    {{0, 2500, -2500, 2500, -2500},  {0, 0, 45, 45, 0}, 5}, // 'Ξ'
    {{0, 2500, 2500, -2500, -2500, 0},  {0, 45, 45, 45, 45, 0},  6}, // 'Ο'
    {{0, 2500, -2500, 0, 0}, {0, 0, 0, 45, 45},  5}, // 'Π'
    {{0, 2500, 2500, 0, -2500}, {0, 0, 45, 45, 45},  5}, // 'Ρ'
    {{0, 2500, -2500, 2500, -2500}, {0, 0, 45, 45, 0}, 5}, // 'Σ'
    {{0, 2500, -2500, 0}, {0, 0, 0, 45},  4}, // 'Τ'
    {{0, 2500, -2500, 0, 0}, {0, 45, 45, 45, -45}, 5}, // 'Υ'
    {{0, 2500, 2500, -2500, -2500, 0}, {0, 45, 45, 45, 45, 0},  6}, // 'Φ'
    {{0, 2500, -2500, 2500, -2500}, {0, 45, 45, -45, -45}, 5}, // 'Χ'
    {{0, 2500, -2500, 2500, -2500}, {0, 45, 45, -45, -45}, 5}, // 'Ψ'
    {{0, 2500, 2500, -2500, -2500, 0}, {0, 45, 45, 45, 45, 0}, 6} // 'Ω'
};
void drawLetter(wchar_t letter) {
    Serial.println("Starting letter drawing...");

    // Check if the input letter is a valid Greek capital letter
    if (letter >= L'Α' && letter <= L'Ω') {  // Check range of Greek capital letters (Α-Ω)
        int index = letter - L'Α';  // Convert Greek letter to an index (0 for 'Α', 1 for 'Β', etc.)
        const Letter& move = letterMovements[index];

        penControl(true);  // Lift the pen initially
        motorX.moveSteps(move.xSteps[0]);  // Move from start position
        motorY.moveSteps(move.ySteps[0]);
        if (move.liftPen[0] == 0) {
            penControl(false);  // Lower the pen to draw if liftPen is 0
        }

        for (int i = 1; i < move.numSteps; i++) {
            if (move.liftPen[i] == 1) {
                penControl(true);  // Lift the pen
                delay(500);
            } else {
                penControl(false);  // Lower the pen
                delay(500);
            }

            motorX.moveSteps(move.xSteps[i]);  // Move according to x and y steps
            motorY.moveSteps(move.ySteps[i]);

            while (motorX.getStepper().isRunning() || motorY.getStepper().isRunning()) {
                motorX.run();
                motorY.run();
                currentPositionX = motorX.getStepper().currentPosition();
                currentPositionY = motorY.getStepper().currentPosition();
            }
        }
        penControl(true);  // Lift the pen after drawing
        delay(500);

         // Move both motors to the home position after drawing the letter
        motorX.moveSteps(HOME_POSITION - currentPositionX);  // Move motor X to home position
      
        // Wait for both motors to reach the home position
        while (motorX.getStepper().isRunning()) {
            motorX.run();
            currentPositionY = motorX.getStepper().currentPosition();
        }

        Serial.println("Returned to home position.");

        delay(500);
        // Move the tape stepper by 220 steps on Y-axis after drawing the letter
        motorY.moveSteps(200);  // Move the Y-axis tape stepper by 220 steps

        // Wait for the motor to finish moving
        while (motorY.getStepper().isRunning()) {
            motorY.run();
            currentPositionY = motorY.getStepper().currentPosition();
        }

        Serial.println("Letter drawing complete and tape moved.");
    } else {
        Serial.println("Invalid Greek letter or unsupported letter.");
    }
}

/*
// Draw the letter based on Greek input (directly uses Greek letter)
void drawLetter(wchar_t letter) {
    Serial.println("Starting letter drawing...");

    // Check if the input letter is a valid Greek capital letter
    if (letter >= L'Α' && letter <= L'Ω') {  // Check range of Greek capital letters (Α-Ω)
        int index = letter - L'Α';  // Convert Greek letter to an index (0 for 'Α', 1 for 'Β', etc.)
        const Letter& move = letterMovements[index];

        penControl(true);  // Lift the pen initially
        motorX.moveSteps(move.xSteps[0]);  // Move from start position
        motorY.moveSteps(move.ySteps[0]);
        if (move.liftPen[0] == 0) {
            penControl(false);  // Lower the pen to draw if liftPen is 0
        }

        for (int i = 1; i < move.numSteps; i++) {
            if (move.liftPen[i] == 1) {
                penControl(true);  // Lift the pen
            } else {
                penControl(false);  // Lower the pen
            }

            motorX.moveSteps(move.xSteps[i]);  // Move according to x and y steps
            motorY.moveSteps(move.ySteps[i]);

            while (motorX.getStepper().isRunning() || motorY.getStepper().isRunning()) {
                motorX.run();
                motorY.run();
                currentPositionX = motorX.getStepper().currentPosition();
                currentPositionY = motorY.getStepper().currentPosition();
            }
        }
        penControl(true);  // Lift the pen after drawing

        // Move the tape stepper by 220 steps on y-axis after drawing the letter
        motorY.moveSteps(220);  // Move the y-axis tape stepper by 220 steps

        // Wait for the motor to finish moving
        while (motorY.getStepper().isRunning()) {
            motorY.run();
            currentPositionX = motorY.getStepper().currentPosition();
        }

        Serial.println("Letter drawing complete and tape moved.");
    } else {
        Serial.println("Invalid Greek letter or unsupported letter.");
    }
}
*/
/*

// Draw the letter based on Greek input (directly uses Greek letter)
void drawLetter(wchar_t letter) {
    Serial.println("Starting letter drawing...");

    // Check if the input letter is a valid Greek capital letter
    if (letter >= L'Α' && letter <= L'Ω') {  // Check range of Greek capital letters (Α-Ζ)
        int index = letter - L'Α';  // Convert Greek letter to an index (0 for 'Α', 1 for 'Β', etc.)
        const Letter& move = letterMovements[index];

        penControl(true);  // Lift the pen initially
        motorX.moveSteps(move.xSteps[0]);  // Move from start position
        motorY.moveSteps(move.ySteps[0]);
        penControl(false);  // Lower the pen to draw

        for (int i = 1; i < move.numSteps; i++) {
            if (i == 7) {
                penControl(true);  // Lift the pen
            }
            if (i == 8) {
                penControl(false);  // Lower the pen
            }

            motorX.moveSteps(move.xSteps[i]);  // Move according to x and y steps
            motorY.moveSteps(move.ySteps[i]);

            while (motorX.getStepper().isRunning() || motorY.getStepper().isRunning()) {
                motorX.run();
                motorY.run();
                currentPositionX = motorX.getStepper().currentPosition();
                currentPositionY = motorY.getStepper().currentPosition();
            }
        }
        penControl(true);  // Lift the pen after drawing
    } else {
        Serial.println("Invalid Greek letter or unsupported letter.");
    }
}
*/
/*

// **Mapping of English letters to Greek letters**
std::map<char, wchar_t> engToGreek = {
    {'A', L'Α'},  // English A to Greek Alpha
    {'B', L'Β'},  // English B to Greek Beta
    {'G', L'Γ'},  // English G to Greek Gamma
    // Add more mappings as needed
};

// Draw the letter based on input
void drawLetter(char letter) {
    Serial.println("Starting letter drawing...");

    // **Convert English letter to Greek letter using the map**
    if (engToGreek.find(letter) != engToGreek.end()) {
        wchar_t greekLetter = engToGreek[letter];  // Get the Greek letter from the map

        // **Calculate the index of the Greek letter in the movements array**
        if (greekLetter >= L'Α' && greekLetter <= L'Ζ') {
            int index = greekLetter - L'Α';  // Index (0 for 'Α', 1 for 'Β', 2 for 'Γ', etc.)
            const Letter& move = letterMovements[index];

            penControl(true);  // Lift the pen initially
            motorX.moveSteps(move.xSteps[0]);  // Move from start position
            motorY.moveSteps(move.ySteps[0]);
            penControl(false);  // Lower the pen to draw

            for (int i = 1; i < move.numSteps; i++) {
                if (i == 7) {
                    penControl(true);  // Lift the pen
                }
                if (i == 8) {
                    penControl(false);  // Lower the pen
                }
                
                motorX.moveSteps(move.xSteps[i]);  // Move according to x and y steps
                motorY.moveSteps(move.ySteps[i]);

                while (motorX.getStepper().isRunning() || motorY.getStepper().isRunning()) {
                    motorX.run();
                    motorY.run();
                    currentPositionX = motorX.getStepper().currentPosition();
                    currentPositionY = motorY.getStepper().currentPosition();
                }
            }
            penControl(true);  // Lift the pen after drawing
        }
    } else {
        Serial.println("Letter not mapped to a Greek equivalent.");
    }
}
*/
/*
//  draw the letter based on input
void drawLetter(const char* letter) {
    Serial.println("Starting letter drawing...");

    if (letter >= 'Α' && letter <= 'Α') {
        int index = letter - 'Α';  // convert letter to array index (0 for 'A', 1 for 'B', etc.)
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
                currentPositionX = motorX.getStepper().currentPosition();
                currentPositionY = motorY.getStepper().currentPosition();
            }
        }
        penControl(true);  // lift the pen after drawing
    }
}

*/
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
    drawVerticalLine(4350*squareSideLength); 
    delay(1000);
    drawHorizontalLine(-235*squareSideLength);
    delay(1000);
    drawVerticalLine(-4350*squareSideLength);
    delay(1000);
}
void drawCircle(int r) {
    Serial.println("Starting to draw a circle...");

    // Motor step resolution for 1 cm (steps per cm)
    const float stepsPerCmX = 2125; // Steps per cm for X motor
    const float stepsPerCmY = 117;  // Steps per cm for Y motor

    // Convert radius (in cm) to steps
    int radiusStepsX = r * stepsPerCmX; // Radius in steps for X motor
    int radiusStepsY = r * stepsPerCmY; // Radius in steps for Y motor

    // Consider a rectangle of size (2r + 1) x (2r + 1)
    int N = 2 * r + 1;

    // Loop through all the points in the square
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Convert square coordinates (i, j) to circle coordinates (x, y)
            int x = i - r;  // Horizontal distance from the center
            int y = j - r;  // Vertical distance from the center

            // Check if the point is inside the circle (x^2 + y^2 <= r^2)
            if (x * x + y * y <= r * r) {
                // Convert the circle coordinates (x, y) to motor steps
                int motorXSteps = x * stepsPerCmX;  // Convert to motor X steps
                int motorYSteps = y * stepsPerCmY;  // Convert to motor Y steps

                motorX.moveSteps(motorXSteps); // Move motor X
                motorY.moveSteps(motorYSteps); // Move motor Y

                // Wait for both motors to reach the target position
                while (motorX.getStepper().isRunning() || motorY.getStepper().isRunning()) {
                    motorX.run();
                    motorY.run();
                }
            }
        }
    }

    Serial.println("Circle drawing complete.");
}

