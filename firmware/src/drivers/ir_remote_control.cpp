#include "drivers/ir_remote_control.h"
#include "drivers/motors.h"
#include <IRremote.hpp>

char32_t last_decoded_raw_data = 0;

// Adjustable speed for IR control
const int IR_DRIVE_SPEED = 180;
const int IR_TURN_SPEED = 120;

void ir_remote_control_init()
{
    IrSender.begin(3);
    IrReceiver.begin(IR_RECEIVER_PIN, false); // Start the receiver
}

// Translate IR signals to motor speeds
void translate_ir_signal()
{
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;

    // Handle repeat codes
    if (IrReceiver.decodedIRData.flags) {
        code = last_decoded_raw_data;
        Serial.println("REPEAT!");
    } else {
        Serial.print("IR code:0x");
        Serial.println(code, HEX);
    }

    int left = 0;
    int right = 0;

    // Map IR buttons to motor speeds
    switch (code) {
        case 0xB946FF00: // UP
            left = -IR_DRIVE_SPEED;
            right = -IR_DRIVE_SPEED;
            Serial.println("IR: UP");
            break;
        case 0xEA15FF00: // DOWN
            left = IR_DRIVE_SPEED;
            right = IR_DRIVE_SPEED;
            Serial.println("IR: DOWN");
            break;
        case 0xBB44FF00: // LEFT
            left = -IR_TURN_SPEED;
            right = IR_TURN_SPEED;
            Serial.println("IR: LEFT");
            break;
        case 0xBC43FF00: // RIGHT
            left = IR_TURN_SPEED;
            right = -IR_TURN_SPEED;
            Serial.println("IR: RIGHT");
            break;
        case 0xBF40FF00: // OK / STOP
            left = 0;
            right = 0;
            Serial.println("IR: STOP");
            break;
        default:
            Serial.println("IR: Other button");
            break;
    }

    set_motors_speed(left, right);
    last_decoded_raw_data = code;

    delay(500); // optional debounce
    IrReceiver.resume();
  }