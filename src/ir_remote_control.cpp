#include "ir_remote_control.h"

uint32_t last_decoded_raw_data = 0;
unsigned long last_command_time;
const unsigned long command_timeout = 200;

void ir_remote_control_init()
{
  IrSender.begin(3);
  IrReceiver.begin(IR_RECEIVER_PIN, false); // Start the receiver
}
// Function to translate IR signals and control the robot
void translate_ir_signal()
{
  if (IrReceiver.decodedIRData.flags)// Check if it is a repeat IR code 
  {
    IrReceiver.decodedIRData.decodedRawData = last_decoded_raw_data;
    Serial.println("REPEAT!");
  } else
  {
    Serial.print("IR code:0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
  }
  // Map IR codes to robot actions
  switch (IrReceiver.decodedIRData.decodedRawData)
  {
    case 0xB946FF00: Serial.println("UP"); Forward();break;
    case 0xEA15FF00: Serial.println("DOWN"); Backward();break;
    case 0xBB44FF00: Serial.println("LEFT"); Left();break;
    case 0xBC43FF00: Serial.println("RIGHT"); Right();   break;
    case 0xBF40FF00: Serial.println("OK"); Stop();   break;
    case 0xAD52FF00: Serial.println("0");    break;
    case 0xE916FF00: Serial.println("1");    break;
    case 0xE619FF00: Serial.println("2");    break;
    case 0xF20DFF00: Serial.println("3");    break;
    case 0xF30CFF00: Serial.println("4");    break;
    case 0xE718FF00: Serial.println("5");    break;
    case 0xA15EFF00: Serial.println("6");    break;
    case 0xF708FF00: Serial.println("7");    break;
    case 0xE31CFF00: Serial.println("8");    break;
    case 0xA55AFF00: Serial.println("9");    break;
    case 0xBD42FF00: Serial.println("*");    break;
    case 0xB54AFF00: Serial.println("#");    break;
    default:
    Serial.println(" other button   ");
  }// End Case  
  last_decoded_raw_data = IrReceiver.decodedIRData.decodedRawData;
  delay(500); 
  IrReceiver.resume(); 
}

