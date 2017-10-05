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
#define SLP_PIN     11
#define IN2_PIN     9
#define IN1_PIN     8
#define PWM_PIN     10
#define PWM_FREQ_DIVISOR    8

#define RELAY_PIN 7

#define DEBUG 1

char readByte;

//this configuration means Stop
char IN1  = 0;
char IN2  = 0;
char SLP  = 1;
char speed = 127;

const int trigPin = 12;
const int echoPin = 13;
int distance;

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


void dc_motor3_brake()
{
  IN1 = IN2 = 1;
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, HIGH);
}

void dc_motor3_stop()
{
  if(SLP != 1)
  {
     SLP = 1;
     digitalWrite(SLP_PIN, HIGH);
  }
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  IN1 = IN2 = 0;  
}

void dc_motor3_standby()
{
  SLP = 0;
  digitalWrite(SLP_PIN, LOW);
}

void dc_motor3_clockwise()
{
  if(SLP != 1)
    SLP = 1;
  IN1 = 0;
  IN2 = 1;
  digitalWrite(SLP_PIN, HIGH);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);  
}

void dc_motor3_counter_clockwise()
{
  if(SLP != 1)
      SLP = 1;
  IN1 = 1;
  IN2 = 0;
  digitalWrite(SLP_PIN, HIGH);
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
}

void dc_motor3_set_speed(char speed)
{
    analogWrite(PWM_PIN, speed);
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

void relay_activate()
{
  digitalWrite(RELAY_PIN, HIGH);
}

void relay_deactivate()
{
  digitalWrite(RELAY_PIN, LOW);
}

void setup() {
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  #ifdef DEBUG
    Serial.println("Debuging mode is ON!");
    Serial.println("Baud rate is 57600");
  #endif
  //ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(RELAY_PIN, OUTPUT);
  //Stepper
  pinMode(ENABLE,OUTPUT);
  pinMode(STEP,OUTPUT);
  pinMode(DIR,OUTPUT);
  //DC motor
  pinMode(SLP_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  
  setPwmFrequency(PWM_PIN, PWM_FREQ_DIVISOR);
  
  dc_motor3_stop();
  dc_motor3_set_speed(speed);
}

int read_distance()
{
  long duration;
  int distanceCm;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  delay(10);
  Serial.print("Distance is: ");
  Serial.println(distanceCm);
  
  return distanceCm;
}

void loop() {
  digitalWrite(ENABLE,LOW);
 
  while(!Serial.available());
  readByte = Serial.read();
  Serial.print("Unesena komanda: ");
  Serial.println(readByte);
  if(readByte == 'a')
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
   else if(readByte == 'w')
  {
    dc_motor3_counter_clockwise();
  }
  else if(readByte == 'x')
  {
    dc_motor3_clockwise();
  }
  else if(readByte == 's')
  {
    dc_motor3_stop();
  }
  else if(readByte == 'r')
  {
    relay_activate();
  }
  else if(readByte == 't')
  {
    relay_deactivate();
  }
  else if(readByte == 'q')
  {
    distance = read_distance();
  }
}
