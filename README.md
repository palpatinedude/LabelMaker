# Label Plotter System

## Overview

This project controls a label plotter that draws letters using a pen attached to a movable platform. The system uses stepper motors to move on X and Y axes, a servo motor to lift and lower the pen, and an ESP32 microcontroller to control everything.

The plotter first finds its home position, then draws Greek letters one by one on a grid. After each letter, it moves the paper to the next position for the next drawing.

---

## Key Features

- **Homing:** Finds the starting position using a push button.
- **Step-by-Step Drawing:** Draws Greek letters one at a time.
- **Servo Control:** Automatically raises and lowers the pen when needed.
- **Label Movement:** Moves the paper after each letter to prepare for the next.

---

## Components Used

- **ESP32 Microcontroller:** Manages motors and button input.
- **Stepper Motors (2):** Move the pen along X and Y axes.
- **Servo Motor:** Controls pen up/down movement.
- **Push Button:** Starts the homing process.

---

## How It Works

1. Press the button to start homing.
2. The plotter moves to the home position.
3. The pen lowers, and the plotter draws a letter.
4. The pen raises, and the paper moves to the next spot.
5. Repeat steps 3 and 4 for each letter.

---
