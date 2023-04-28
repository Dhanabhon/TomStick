/*
    TomStick.h - Library for controlling the axes of the joystick.
    Created by Tom Dhanabhon, Jan 14, 2023.
*/

#ifndef _____TomStick__
#define _____TomStick__

#include <Arduino.h>

class TomStick {
    public:
        enum Direction {
            UP = 0,
            DOWN = 1,
            LEFT = 2,
            RIGHT = 3,
            UP_RIGHT = 4,
            UP_LEFT = 5,
            DOWN_RIGHT = 6,
            DOWN_LEFT = 7,
            CENTER = 8,
            UNKNOWN = 9
        };

        struct JoystickInfo
        {
            int AxisX;
            int AxisY;
            int DeadZoneThreshold;
        };
        
        TomStick(byte x_pin, byte y_pin);
        void begin(void);

        int readRawAxisX(void);
        int readRawAxisY(void);
        void calibrate(void);
        Direction onMove(void);
        void setDeadzoneThreshold(int);

        JoystickInfo joystickInfo;
        
    private:
        int xValue = 0; // Variable to store X axis value
        int yValue = 0; // Variable to store Y axis value

        int xCenter = 512; // X axis center value
        int yCenter = 512; // Y axis center value

        int threshold = 50; // Joystick movement threshold (deadzone)

        byte X_PIN;
        byte Y_PIN;
};

#endif