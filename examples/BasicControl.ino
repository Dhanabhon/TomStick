#include <TomStick.h>

#define JOYSTICK_X_PIN          A0
#define JOYSTICK_Y_PIN          A1

TomStick joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN);

void setup() {
    Serial.begin(115200);
    
    // Initialize the joystick values
    joystick.begin();
    // Calibreate the joystick center position
    joystick.calibrate();
}

void loop() {
    joystick.onMove();

    Serial.print("X: ");
    Serial.print(joystick.joystickInfo.AxisX);
    Serial.print(" ,Y: ");
    Serial.print(joystick.joystickInfo.AxisY);
    Serial.println();

    delay(50);
}