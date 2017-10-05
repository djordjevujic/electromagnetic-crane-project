//Source code for complete crane components

//Stepper parameters
#define ENABLE 6
#define STEP 4
#define DIR 2

#define STEPS_PER_ROTATION 200
#define STEPPING_SCALE     4
#define STEPPER_CW         HIGH
#define STEPPER_CCW        LOW

//DC motor parameters


#define DEBUG 1

char readByte;

void setup() {
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  #ifdef DEBUG
    Serial.println("Debuging mode is ON!");
    Serial.println("Baud rate is 57600");
  #endif
  pinMode(ENABLE,OUTPUT);
  pinMode(STEP,OUTPUT);
  pinMode(DIR,OUTPUT);
}


void stepNow(int totalSteps) {
  Serial.print(totalSteps);
  Serial.println(F(" steps."));

  int i;
  totalSteps = totalSteps * STEPPING_SCALE;
  for(i=0;i<totalSteps;++i) {
    digitalWrite(STEP,HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP,LOW);
    delayMicroseconds(2000);
  }
}

void stepper_move(int step_dir, int steps)
{
  Serial.print("stepper_move: ");
  Serial.print(step_dir);
  Serial.print(", ");
  Serial.println(steps);
  
  digitalWrite(DIR, step_dir);
  stepNow(steps);
}

void loop() {
  digitalWrite(ENABLE,LOW);
 
  while(!Serial.available());
  if((readByte = Serial.read()) == 'a')
  {
     stepper_move(STEPPER_CW, STEPS_PER_ROTATION/4);
    //walkOneDirection();
    Serial.println("Function stepper_move(cw, steps_per_rot / 4) executed!");
  }
  else if(readByte == 'z')
  {
    stepper_move(STEPPER_CCW, STEPS_PER_ROTATION/4);
    Serial.println("Function stepper_move(ccw, steps_per_rot / 4) executed!");
  }
}
