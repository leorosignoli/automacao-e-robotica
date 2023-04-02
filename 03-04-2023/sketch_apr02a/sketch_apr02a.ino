#include <SimpleModbusSlave.h>

enum{
  POT_1,
  POT_2,
  POT_3,
  HOLDING_REGS_SIZE
};

unsigned int holdingRegs[HOLDING_REGS_SIZE];

void setup() {
  modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs);
  modbus_update_coms(9600, SERIAL_8N1, 1);

}

void loop() {
  modbus_update();

  holdingRegs[POT_1] = analogRead(A0);
  holdingRegs[POT_2] = analogRead(A1);
  holdingRegs[POT_3] = analogRead(A2);
}
