// This example shows how to send I2C commands to two Tic Stepper
// Motor Controllers on the same I2C bus.
//
// Each Tic's control mode must be set to "Serial/I2C/USB".  The
// serial device number of one Tic must be set to its default
// value of 14, and the serial device number of another Tic must
// be set to 15.
//
// The GND, SCL, and SDA pins of the Arduino must each be
// connected to the corresponding pins on each Tic.  You might
// consider connecting the ERR lines of both Tics so that if
// either one experiences an error, both of them will shut down
// until you reset the Arduino.
//
// See the comments and instructions in I2CSpeedControl.ino for
// more information.

#include <Tic.h>
#include <Timer.h>
#include "stepper.h"
#include "motion_control.h"

Stepper StepperT(10);
Stepper StepperY(11);
Stepper StepperX(12);

// Initialisation of the motors controller
Motion_control Controller(&StepperX, &StepperY, &StepperT);

SemaphoreHandle_t syncSemaphoreTimeOut;
SemaphoreHandle_t syncSemaphoreStep;

hw_timer_t * syncTimerTimeOut = NULL;
hw_timer_t * syncTimerStep = NULL;

void IRAM_ATTR handleTimeOut(){
  //Can't use Serial or I2C in interrupt
  xSemaphoreGiveFromISR(syncSemaphoreTimeOut, NULL);
}

void IRAM_ATTR handleStep(){
  //Can't use Serial or I2C in interrupt
  xSemaphoreGiveFromISR(syncSemaphoreStep, NULL);
}


void skeletonTask( void * parameter )
{
  /* Block for 1 second */
  const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
  while( true) {
    
    if(xSemaphoreTake(syncSemaphore1, xDelay)){
      Serial.printf("Motion detected 11, %d pending\n",uxSemaphoreGetCount(syncSemaphore1));
    } 
    else {
      Serial.printf("no synch1 in last second\n");
    }
  }
    vTaskDelete( NULL );
}


void setup()
{
  Wire.begin();
  delay(20);
  Serial.begin(115200);

  // Init of the semaphores
  syncSemaphoreTimeOut = xSemaphoreCreateBinary();
  syncTimerStep = xSemaphoreCreateBinary();

  // Use 1st timer of 4 (counted from zero) for timeout
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
  // info).
  timer = timerBegin(0, 80, true);
  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &handleTimeOut, true);

  xTaskCreate(
    skeletonTask, // Task function.
    "Producer", // String with name of task.
    10000, // Stack size in words.
    NULL, // Parameter passed as input of the task
    1, // Priority of the task.
    NULL); // Task handle.

  StepperT.init();
  StepperY.init();
  StepperX.init();
}

void loop()
{

    Controller.calibrate();
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
