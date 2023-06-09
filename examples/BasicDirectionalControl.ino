#include <TomStick.h>

#define JOYSTICK_X_PIN          A0
#define JOYSTICK_Y_PIN          A1

TomStick joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN);
TomStick::Direction currentJoystickState = TomStick::UNKNOWN;

void setup() {
    Serial.begin(115200);
    
    // Initialize the joystick values
    joystick.begin();
    // Calibreate the joystick center position
    joystick.calibrate();
}

void loop() {
    currentJoystickState = joystick.onMove();

    switch (currentJoystickState)
    {
    case TomStick::CENTER:
      Serial.println("CENTER");
      break;
    case TomStick::UP_LEFT:
      Serial.println("UP-LEFT");
      break;
    case TomStick::UP:
      Serial.println("UP");
      break;
    case TomStick::UP_RIGHT:
      Serial.println("UP-RIGHT");
      break;
    case TomStick::LEFT:
      Serial.println("LEFT");
      break;
    case TomStick::RIGHT:
      Serial.println("RIGHT");
      break;
    case TomStick::DOWN_LEFT:
      Serial.println("DONW-LEFT");
      break;
    case TomStick::DOWN:
      Serial.println("DOWN");
      break;
    case TomStick::DOWN_RIGHT:
      Serial.println("DOWN-RIGHT");
      break;
    default:
      Serial.println("UNKNOWN");
      break;
    }
}