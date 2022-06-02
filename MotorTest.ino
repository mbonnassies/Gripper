#include <Wire.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;
// Motor A
 
int enA = 9; // Motor speed (PWM with values from 0 to 255)
int in1 = 8; // One pin of the motor
int in2 = 7; // Other pin of the motor (depending on which one is set to HIGH it'll decide the direction of rotation)
int JoyVert = A0; // Vertical joystick position
int JoyHor = A1; // Horizontal joystick position
int Pot = A2; // Potentiometer pin (will give values from 0 to 1023)

int MotorSpeed = 0;
int JoyPosVert = 512; //Vertical resting position
int JoyPosHor = 512; //Horizontal resting position
int PotValue = 0;
 
void setup()
 
{
 
  // Set all the motor control pins to outputs
 
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(enA, LOW); //Start with motor speed of 0 (and going forward)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

 Serial.begin(115200);

  uint32_t currentFrequency;
    
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
  
  Serial.println("Measuring voltage and current with INA219 ...");
}
 
void loop() {
  
  PotValue = analogRead(Pot); // Values from 0 to 1023
  JoyPosVert = analogRead(JoyVert); // Values from 0 to 1023
  JoyPosHor = analogRead(JoyHor);
 
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
    if (JoyPosVert < 460) { //backwards
     digitalWrite(in1, LOW);
     digitalWrite(in2, HIGH);

      // Mapping to MotorSpeed:

     JoyPosVert = JoyPosVert - 460; 
     JoyPosVert = JoyPosVert * (-1); // So we end up with values from 0 to 460 increasing with speed

     MotorSpeed = map(JoyPosVert, 0, 460, 0, 170); // Motor can go up to 255 bu we put 170 cause we don't need it to turn that fast
   }
   else if (JoyPosVert > 564) {
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);

     MotorSpeed = map(JoyPosVert, 564, 1023, 0, 170);
   }
   else if (JoyPosVert>460 && JoyPosVert<564) {
    MotorSpeed=0;
   }

  Serial.println(PotValue);
  Serial.println(MotorSpeed);
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

  delay(100); 

  if (MotorSpeed > 255) {MotorSpeed=255;} //Shouldn't happen but just in case
  if (MotorSpeed < 8) {MotorSpeed=0;} //To prevent buzzing
  
  analogWrite(enA, MotorSpeed); // Make the motor turn at the speed calculated from joystick position
 
  
}
