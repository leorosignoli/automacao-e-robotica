#include "SimpleModbusSlaveV10/SimpleModbusSlave.h"
#include "SimpleModbusSlaveV10/SimpleModbusSlave.cpp"


#define RELAY_PORT 2
#define LIGHT_SENSOR_PORT A5
#define HUMIDITY_SENSOR_PORT 6

enum{
  HUMIDITY_SENSOR_VALUE,
  LIGHT_SENSOR_VALUE,
  RELAY_TOGGLE,
  HOLDING_REGS_SIZE
};

unsigned int holdingRegs[HOLDING_REGS_SIZE];

void setup() {
  Serial.begin(9600);
  modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs);
  pinMode(RELAY_PORT, OUTPUT); 
  pinMode(LIGHT_SENSOR_PORT, INPUT); 
  modbus_update_comms(9600, SERIAL_8N1, 1);
}

int previousRelayToggle = 0; 
void loop() {
  modbus_update();
  holdingRegs[HUMIDITY_SENSOR_VALUE]= digitalRead(RELAY_PORT);
  holdingRegs[LIGHT_SENSOR_VALUE]= analogRead(LIGHT_SENSOR_PORT);

//\\  if ( 2 == holdingRegs[RELAY_TOGGLE])
//  \\    digitalWrite(RELAY_PORT, 0 );
// \\ else if ( 3 == holdingRegs[RELAY_TOGGLE])
//   \\   digitalWrite(RELAY_PORT, 1 );


}
