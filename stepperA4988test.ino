// A4988 driver test routine
/* 
 * STEPPER 2 CLICK:
 *  supply voltage: 12V (energetic)
 *                  3.3V or 5V (electronic)
 *                 
 * Connecting pins:
 * STEPPER 2 CLICK      Arduino     
 *  EN------------------6
 *  RST-----------------VCC
 *  SL------------------VCC
 *  DIR-----------------2
 *  ST------------------4
 *  Don't forget to connect grounds and VCC (3.3V or 5V are compatible)
*/

#define ENABLE 6
#define STEP 4
#define DIR 2

#define STEPS_PER_ROTATION 200
#define STEPPING_SCALE     4

#define DEBUG 1

char readByte;

void setup() {
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  #ifdef DEBUG
    Serial.println("Debuging mode is ON!");
  #endif
  pinMode(ENABLE,OUTPUT);
  pinMode(STEP,OUTPUT);
  pinMode(DIR,OUTPUT);
}


void stepNow(int totalSteps) {
  Serial.print(totalSteps);
  Serial.println(F(" steps."));

  int i;
  for(i=0;i<totalSteps;++i) {
    digitalWrite(STEP,HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP,LOW);
    delayMicroseconds(2000);
  }
}

void walkOneCircle()
{
  #ifdef DEBUG
    Serial.println("walkOneCircle function called!");
  #endif
  stepNow(STEPS_PER_ROTATION*STEPPING_SCALE);  
}

void walkOneDirection()
{
  Serial.println("walkOneDirection");
  Serial.println("dir LOW");
  digitalWrite(DIR, HIGH);
  stepNow(STEPS_PER_ROTATION);  
}

void walkBothDirections() {
  Serial.println(F("dir LOW"));
  digitalWrite(DIR,LOW);
  stepNow(STEPS_PER_ROTATION);
  delay(1000);
  Serial.println(F("dir HIGH"));
  digitalWrite(DIR,HIGH);
  stepNow(STEPS_PER_ROTATION);
}

void loop() {
  digitalWrite(ENABLE,LOW);
 
  while(!Serial.available());
  if((readByte = Serial.read()) == 'a')
  {
    walkOneCircle();
    Serial.println("One circle is made!");
  }
  //delay(2000);
  //Serial.println(F("Enable LOW"));
  //digitalWrite(ENABLE,LOW);
  //walkBothDirections();
}
