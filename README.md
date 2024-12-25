This project is for controlling a label plotter system that draws letters using a pen mounted on a movable platform. The plotter uses stepper motors to control the movement on the X and Y axes,
a servo motor to lift and lower the pen, and an ESP32 microcontroller to handle the overall control.
Overview

The label plotter starts by "homing" the system to find its reference position, then it proceeds to draw labels (Greek letters, in this case) on a predefined grid. After each letter is drawn,
the plotter moves the paper (by rotating a stepper motor) to the next position for the next letter.
Key Features:

    Homing: The system finds its home position using a button before starting the drawing process or reach max position.
    Step-by-Step Drawing: The plotter draws Greek letters one by one.
    Servo Control: The pen is automatically raised and lowered based what is neccessary.
    Label Movement: After drawing each letter, the plotter moves the paper to the next spot for drawing the next letter.

Components Used:
    ESP32 Microcontroller: Handles motor control, servo, and button input.
    Stepper Motors (2): Drive the X and Y axes for drawing the labels.
    Servo Motor: Controls the pen up and down function for drawing.
    Push Button: Used to initiate the homing process.
