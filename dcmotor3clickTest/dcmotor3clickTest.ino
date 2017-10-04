/*
 * TB6549FG Motorola DC driver
 * DC MOTOR3 click
 *  supply voltage: max 30V (energetic)
 *                  5V (electronics)
 *  Connecting pins 
 *  DCMotor3Click       Arduino
 *  SLP-----------------11
 *  IN1-----------------8
 *  IN2-----------------9
 *  PWM-----------------10
 *  
 *  The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.

 *  divisors for 3 and 11 are 1,8,32,64,128,256,1024
 *  divsors  for 5, 6, 9 and 10 are 1, 8, 64, 256, 1024
*/

#define SLP_PIN     11
#define IN2_PIN     9
#define IN1_PIN     8
#define PWM_PIN     10

#define PWM_FREQ_DIVISOR    8

//this configuration means Stop
char IN1  = 0;
char IN2  = 0;
char SLP  = 1;
char speed = 127;

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
  digitalWrite(IN2_PIN, LOW);
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

void setup() {
  // put your setup code here, to run once:
 
  pinMode(SLP_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);

  setPwmFrequency(PWM_PIN, PWM_FREQ_DIVISOR);

  //dc_motor3_counter_clockwise();
  dc_motor3_set_speed(speed);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
