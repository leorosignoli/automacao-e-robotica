#include "SimpleModbusSlaveV10/SimpleModbusSlave.h"
#include "SimpleModbusSlaveV10/SimpleModbusSlave.cpp"
#include "ArduinoThread-master/Thread.h"
#include "ArduinoThread-master/Thread.cpp"
#include "ArduinoThread-master/ThreadController.h"
#include "ArduinoThread-master/ThreadController.cpp"

#include <Stepper.h>

#define STEPS 100 // uma icognita bem misteriosa que nao sei o que faz


#define MOTOR_1_PORT 2
#define MOTOR_2_PORT 3
#define MOTOR_3_PORT 4
#define MOTOR_4_PORT 5


enum {
  MOTOR_SPEED,
  HOLDING_REGS_SIZE
};
unsigned int holdingRegs[HOLDING_REGS_SIZE];

ThreadController controll = ThreadController();  // ThreadController that will controll all threads
Thread motor1Thread = Thread();

Stepper stepper(STEPS, MOTOR_1_PORT, MOTOR_2_PORT, MOTOR_3_PORT, MOTOR_4_PORT);

int previousMotorSpeed = 0;
void rotateMotor(int motorSpeed){
  stepper.step(motorSpeed - previousMotorSpeed);
  previousMotorSpeed = motorSpeed;
}

void thread1Callback(){
  rotateMotor(MOTOR_SPEED);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs );
  modbus_update_comms(9600, SERIAL_8N1, 1);
//  
  stepper.setSpeed(60); // Velocidade de rotação
//
//  
//  
//  motor1Thread.setInterval(100);
//  motor1Thread.onRun(thread1Callback);
//  motor1Thread.setInterval(12);
//  controll.add(&motor1Thread);
}

void loop() {
  
  modbus_update();

  digitalWrite(LED_BUILTIN, HIGH);


//  controll.run();

  stepper.setSpeed( 1+ holdingRegs[MOTOR_SPEED] ); // Velocidade de rotação
  stepper.step( 32 );  // gira N unidades de angulo
}
