#include "stepper.h"
#include "motion_control.h"
#include "calibration.h"
#include <Tic.h>
#include <DebounceInput.h>

Stepper StepperT(10);
Stepper StepperY(11);
Stepper StepperX(12);

const int timeStep = 10; //Time step of step tracking in useconds
const int xSwitchPin = 12;
const int ySwitchPin = 13;

DebouncedInput xSwitchPinDB;
DebouncedInput ySwitchPinDB;

// Initialisation of the motors controller
Motion_control Controller(&StepperX, &StepperY, &StepperT);

// Initialisation of the TimeOut timer (Tic need a communication every second
// or they stop with timeout exeption
hw_timer_t * syncTimerTimeOut = NULL;
volatile SemaphoreHandle_t syncTimerTimeOutSemaphore;

// Initialisation of the step timer
hw_timer_t * syncTimerStep = NULL;
volatile SemaphoreHandle_t syncTimerStepSemaphore;

//Definition of The Interrupt Service Routine for Timeout
void IRAM_ATTR onsyncTimerTimeOut(){
  xSemaphoreGiveFromISR(syncTimerTimeOutSemaphore, NULL);
}

//Definition of The Interrupt Service Routine for step
void IRAM_ATTR onsyncTimerStep(){
  xSemaphoreGiveFromISR(syncTimerStepSemaphore, NULL);
}

void timeOutTask( void * parameter )
{
  /* Block for 1 second */
  const TickType_t xDelay = 1000;
  bool state = true;
  while(true) {
    if(xSemaphoreTake(syncTimerTimeOutSemaphore, xDelay)){
      Controller.resetTimeout();
    } 
    else {}
  }
    vTaskDelete( NULL );
}

void stepTask( void * parameter )
{
  /* Block for 1 second */
  const TickType_t xDelay = 1000;
  bool state = true;
  while(true) {
    if(xSemaphoreTake(syncTimerTimeOutSemaphore, xDelay)){
      Controller.resetTimeout();
    } 
    else {}
  }
    vTaskDelete( NULL );
}

int counter = 0;

void setup() {
  Serial.begin(115200);
  delay(20);
  Wire.begin();
  
  pinMode(ySwitchPin, INPUT_PULLUP);
  pinMode(xSwitchPin, INPUT_PULLUP);
  xSwitchPinDB.attach(xSwitchPin);
  ySwitchPinDB.attach(ySwitchPin);

  // Create semaphore to inform us when the syncTimerTimeOut has fired
  syncTimerTimeOutSemaphore = xSemaphoreCreateBinary();

  // Use 1st syncTimerTimeOut of 4 (counted from zero).
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
  // info).
  syncTimerTimeOut = timerBegin(0, 80, true);

  // Attach onsyncTimerTimeOut function to our syncTimerTimeOut.
  timerAttachInterrupt(syncTimerTimeOut, &onsyncTimerTimeOut, true);

  // Set alarm to call onsyncTimerTimeOut function every second (value in microseconds).
  // Repeat the alarm (third parameter)
  timerAlarmWrite(syncTimerTimeOut, 900000, true);

  // Start an alarm
  timerAlarmEnable(syncTimerTimeOut);

  Controller.init();

  xTaskCreate(
    timeOutTask, // Task function.
    "TimeOut", // String with name of task.
    10000, // Stack size in words.
    NULL, // Parameter passed as input of the task
    1, // Priority of the task.
    NULL); // Task handle.
  calibrationXY(&StepperX, &StepperY, &xSwitchPinDB, &ySwitchPinDB);
}

void loop() {
  xSwitchPinDB.read();
  if(xSwitchPinDB.changing()){counter++;}
  Serial.println(counter);
  delay(1000);
//  Serial.println(StepperY.getMicro_step());
//  Serial.println("yolo");
//  StepperT.setTargetVelocity(2000000);
//  StepperY.setTargetVelocity(0);
//  delayWhileResettingCommandTimeout(1000);
//
//  StepperT.setTargetVelocity(0);
//  StepperY.setTargetVelocity(2000000);
//  delayWhileResettingCommandTimeout(1000);
//
//  StepperT.setTargetVelocity(-2000000);
//  StepperY.setTargetVelocity(0);
//  delayWhileResettingCommandTimeout(1000);
//
//  StepperT.setTargetVelocity(0);
//  StepperY.setTargetVelocity(-2000000);
//  delayWhileResettingCommandTimeout(1000);
}
