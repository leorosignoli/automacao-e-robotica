#include "SimpleModbusSlaveV10/SimpleModbusSlave.h"
#include "SimpleModbusSlaveV10/SimpleModbusSlave.cpp"

#define BLUE_LED 9
#define GREEN_LED 10
#define RED_LED 11
#define CHAVE 2

enum{
  VALOR_POTR,
  VALOR_POTG,
  VALOR_POTB,
  VALOR_ELIPSER,
  VALOR_ELIPSEG,
  VALOR_ELIPSEB,
  VALOR_PWMR,
  VALOR_PWMG,
  VALOR_PWMB,
  MAN_AUTO,
  HOLDING_REGS_SIZE
};

unsigned int holdingRegs[HOLDING_REGS_SIZE];


void setup() {
  modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs);

}

void loop() {
  

  modbus_update();

  holdingRegs[VALOR_POTR] = analogRead(A0);
  holdingRegs[VALOR_POTG] = analogRead(A1);
  holdingRegs[VALOR_POTB] = analogRead(A2);
  holdingRegs[MAN_AUTO] = analogRead(CHAVE);

  if(holdingRegs[MAN_AUTO]==0){
    holdingRegs[VALOR_PWMR] = map(holdingRegs[VALOR_PWMR], 0, 1023, 0, 255);
    analogWrite(RED_LED, holdingRegs[VALOR_PWMR]);

    holdingRegs[VALOR_PWMB] = map(holdingRegs[VALOR_PWMR], 0, 1023, 0, 255);
    analogWrite(BLUE_LED, holdingRegs[VALOR_PWMB]);

    holdingRegs[VALOR_PWMG] = map(holdingRegs[VALOR_PWMR], 0, 1023, 0, 255);
    analogWrite(GREEN_LED, holdingRegs[VALOR_PWMG]);
  } else {
    holdingRegs[VALOR_PWMR] = holdingRegs[VALOR_ELIPSER];
    analogWrite(RED_LED, holdingRegs[VALOR_PWMR]);

    holdingRegs[VALOR_PWMG] = holdingRegs[VALOR_ELIPSEG];
    analogWrite(GREEN_LED, holdingRegs[VALOR_PWMG]);

    holdingRegs[VALOR_PWMB] = holdingRegs[VALOR_ELIPSEB];
    analogWrite(BLUE_LED, holdingRegs[VALOR_PWMB]);
  }

}
