
#include "SimpleModbusSlaveV10/SimpleModbusSlave.h"
#include "SimpleModbusSlaveV10/SimpleModbusSlave.cpp" 

#define RELAY_PORT 12

enum{
  RELAY_VALUE,
  MOTOR_SPEED,
  HOLDING_REGS_SIZE
};

unsigned int holdingRegs[HOLDING_REGS_SIZE];


void setup() {
  Serial.begin(9600);
  modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs);
   pinMode(RELAY_PORT, OUTPUT); 
   modbus_update_comms(9600, SERIAL_8N1, 1);

}

int switchVal = 0;

void loop() {
  modbus_update();
  holdingRegs[RELAY_VALUE] = digitalRead(RELAY_PORT);
  Serial.println(digitalRead(RELAY_PORT));
  if (switchVal% 2 != 0){
    digitalWrite(RELAY_PORT,HIGH);
  }
  else {
    digitalWrite(RELAY_PORT,LOW);
  }
  switchVal++;
  delay(10000); 

}
