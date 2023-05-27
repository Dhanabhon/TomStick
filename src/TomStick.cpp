#include "TomStick.h"

TomStick::TomStick(byte x_pin, byte y_pin) {
    this->X_PIN = x_pin;
    this->Y_PIN = y_pin;
}

void TomStick::begin(void) {
    pinMode(X_PIN, INPUT);
    pinMode(Y_PIN, INPUT);

    joystickInfo.AxisX = 0;
    joystickInfo.AxisY = 0;
    joystickInfo.DeadZoneThreshold = threshold;
}

int TomStick::readRawAxisX(void) {
    return analogRead(X_PIN);
}

int TomStick::readRawAxisY(void) {
    return analogRead(Y_PIN);
}

void TomStick::calibrate() {
    int totalX = 0, totalY = 0;
    int count = 10;
    unsigned long startTime = millis();
    unsigned long elapsedTime = 0;
    int samples = 0;
    while (samples < count) {
        if (elapsedTime >= 50) {
            totalX += analogRead(X_PIN);
            totalY += analogRead(Y_PIN);
            samples++;
            elapsedTime = 0;
        }
        elapsedTime = millis() - startTime;
    }
    xCenter = totalX / count;
    yCenter = totalY / count;
}

/// @brief The threshold value, which represents the deadzone value of the joystick, should be set between 0 and 100.
/// @param threshold 
void TomStick::setDeadZoneThreshold(int threshold = 50) {
    threshold = abs(threshold);

    if (threshold > 512) {
        threshold = 512;
    }

    this->threshold = threshold;
    joystickInfo.DeadZoneThreshold = this->threshold;
}

TomStick::Direction TomStick::onMove(void) {
    Direction currentDirection = UNKNOWN;

    // Read X and Y axis values
    xValue = readRawAxisX();
    yValue = readRawAxisY();

    // Calibrate X and Y axis values
    xValue = xValue - xCenter;
    yValue = yValue - yCenter;

    joystickInfo.AxisX = xValue;
    joystickInfo.AxisY = yValue;

    // Check if joystick has moved beyond threshold
    if (abs(xValue) > threshold || abs(yValue) > threshold) {
        // Detect joystick direction
        if (xValue > threshold && yValue > threshold) {
            currentDirection = DOWN_RIGHT;
        } else if (xValue > threshold && yValue < -threshold) {
            currentDirection = UP_RIGHT;
        } else if (xValue < -threshold && yValue > threshold) {
            currentDirection = DOWN_LEFT;
        } else if (xValue < -threshold && yValue < -threshold) {
            currentDirection = UP_LEFT;
        } else if (xValue > threshold) {
            currentDirection = RIGHT;
        } else if (xValue < -threshold) {
            currentDirection = LEFT;
        } else if (yValue > threshold) {
            currentDirection = DOWN;
        } else if (yValue < -threshold) {
            currentDirection = UP;
        } else {
            currentDirection = UNKNOWN;
        }
    } else {
        currentDirection = CENTER;
    }

    return currentDirection;
}