#include <PID_v1.h>
#include "lm335.c"
#include <math.h>

#define TEMP_INPUT_PIN 0
#define PWM_OUTPUT_PIN 3

//value written to OCR2A register to set PWM frequency
int PWM_divisor = 63;

//Define PID Variables we'll be connecting to
double Setpoint, Input, Output;
//might not need this
int integer_out;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  
  pinMode(3, OUTPUT);
  //pinMode(11, OUTPUT);
  //sets up PWM
  TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  
  //CS2x bits control timer prescaler. 
  //writing 001 to CS22, CS21, CS20 means no prescaling 
  TCCR2B = _BV(WGM22) | _BV(CS20);

  // OCR2A determines the frequency. 63 is roughly 250kHz 
  OCR2A = PWM_divisor;
  // OCRB determins the duty cycle. more specifically, OCR2A/OCR2B determines the duty cycle.
  // 31 is a duty cycle of 50%
  OCR2B = 0;


  //initialize the variables we're linked to
  Input = getCelciusLM335();
  //setpoint will be in degrees celcius
  Setpoint = 15.0;

  //clamps PID output to min,max values
  myPID.SetOutputLimits(0,PWM_divisor);
  //turn the PID on
  myPID.SetMode(AUTOMATIC);

}

void loop() {
  //get temp from LM335
  Input = getCelciusLM335();
  myPID.Compute();
  
  //THis below line might work. Not sure if it uses default PWM frequency or something else
  analogWrite(PWM_OUTPUT_PIN, Output);
  
  //may also want to try
  //integer_out = (int) (round(Output));
  //OCRB = integer_out;

  
  
}
