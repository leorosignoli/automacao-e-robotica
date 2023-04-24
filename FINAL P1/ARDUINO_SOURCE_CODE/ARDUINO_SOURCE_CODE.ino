#include "SimpleModbusSlaveV10/SimpleModbusSlave.h"
#include "SimpleModbusSlaveV10/SimpleModbusSlave.cpp"

//LED ports
#define BLUE_LED_PORT 9
#define GREEN_LED_PORT 10
#define RED_LED_PORT 11
#define SWITCH_PORT 12

//Potenciometer ports
#define BLUE_POT_PORT A0
#define GREEN_POT_PORT A1
#define RED_POT_PORT A2

#define TEMP_SENSOR_PORT 8
#define LIGHT_SENSOR_PORT A4
#define RELAY_PORT 13

#define LUMINOSITY_LIMIT 600

enum {
  POT_BLUE,
  POT_GREEN,
  POT_RED,
  ELIPSE_SLIDER_BLUE,
  ELIPSE_SLIDER_GREEN,
  ELIPSE_SLIDER_RED,
  PWM_RED,
  PWM_BLUE,
  PWM_GREEN,
  MANUAL_LED_SWITCH_VALUE,
  RELAY_SWITCH,
  TEMP_ALARM_TOGGLE,
  LIGHT_SENSOR_VALUE,
  TEMPERATURE_SENSOR_VALUE,
  HOLDING_REGS_SIZE
};

unsigned int holdingRegs[HOLDING_REGS_SIZE];

void setup() {
  modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs);
  modbus_update_comms(9600, SERIAL_8N1, 1);
  pinMode(BLUE_LED_PORT, OUTPUT); 
  pinMode(GREEN_LED_PORT, OUTPUT); 
  pinMode(RED_LED_PORT, OUTPUT); 
  pinMode(SWITCH_PORT, INPUT);
  pinMode(RELAY_PORT, OUTPUT);
  pinMode(TEMP_SENSOR_PORT, INPUT);
}

void loop() {
  modbus_update();

  setPotenciometerValues();
  setSwitchValue();

  if ( !isSwitchOn() ) {
     writePotenciometerValuesToLed();
  } else {
     writeSliderValuesToLed();
  }

  checkRelayToggle();

  checkIfTemperatureExceedsLimit();

  checkSensors();

  //printValues();

}

void printValues(){
  
  Serial.print(holdingRegs[POT_BLUE]);
  Serial.print("\n");
  Serial.print(holdingRegs[POT_GREEN]);
  Serial.print("\n");
  Serial.print(holdingRegs[POT_RED]);
}
void checkSensors(){
  holdingRegs[LIGHT_SENSOR_VALUE] = analogRead(LIGHT_SENSOR_PORT);
}

void checkIfTemperatureExceedsLimit(){
  if (analogRead(TEMP_SENSOR_PORT) > LUMINOSITY_LIMIT)
    holdingRegs[TEMP_ALARM_TOGGLE] = 1;
  else
    holdingRegs[TEMP_ALARM_TOGGLE] = 0;
  
}

void setPotenciometerValues() {
  
  holdingRegs[POT_BLUE] = analogRead(BLUE_POT_PORT);
  holdingRegs[POT_GREEN] = analogRead(GREEN_POT_PORT);
  holdingRegs[POT_RED] = analogRead(RED_POT_PORT);
  
  holdingRegs[BLUE_LED_PORT] = analogRead(BLUE_POT_PORT);
  holdingRegs[GREEN_LED_PORT] = analogRead(GREEN_POT_PORT);
  holdingRegs[RED_LED_PORT] = analogRead(RED_POT_PORT);
}

void setSwitchValue() {
  holdingRegs[MANUAL_LED_SWITCH_VALUE] = digitalRead(SWITCH_PORT);
}

boolean isSwitchOn() {
  return holdingRegs[MANUAL_LED_SWITCH_VALUE] == 1 ;
}


void writePotenciometerValuesToLed(){
 holdingRegs[PWM_RED]= map(holdingRegs[POT_RED], 0, 1023, 0, 255);
 holdingRegs[PWM_GREEN]= map(holdingRegs[POT_GREEN], 0, 1023, 0, 255);
 holdingRegs[PWM_BLUE]= map(holdingRegs[POT_BLUE], 0, 1023, 0, 255);
 writeToLed(holdingRegs[PWM_RED], holdingRegs[PWM_GREEN], holdingRegs[PWM_BLUE]);
}

void writeSliderValuesToLed(){
  holdingRegs[PWM_RED] = holdingRegs[ELIPSE_SLIDER_RED];
  holdingRegs[PWM_GREEN] = holdingRegs[ELIPSE_SLIDER_GREEN];
  holdingRegs[PWM_BLUE] = holdingRegs[ELIPSE_SLIDER_BLUE];
  writeToLed(holdingRegs[PWM_RED], holdingRegs[PWM_GREEN], holdingRegs[PWM_BLUE]);
}

void writeToLed(int red, int green, int blue){
  analogWrite(BLUE_LED_PORT, (int)blue/4);
  analogWrite(RED_LED_PORT, (int)red/4);
  analogWrite(GREEN_LED_PORT, (int)green/4);
}

void checkRelayToggle(){
  if (holdingRegs[RELAY_SWITCH] == 1 ) {
    digitalWrite(RELAY_PORT, HIGH);
  } else if( holdingRegs[RELAY_SWITCH] ==  0 ){
    digitalWrite(RELAY_PORT, LOW);
  }
}
