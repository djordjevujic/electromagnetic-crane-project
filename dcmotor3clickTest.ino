/*
 * TB6549FG Motorola DC driver
 * DC MOTOR3 click
 *  supply voltage: max 30V (energetic)
 *                  5V (electronics)
 *  Connecting pins 
 *  DCMotor3Click       Arduino
 *  SLP-----------------10
 *  IN1-----------------8
 *  IN2-----------------9
 *  PWM-----------------3
*/

#define SLP_PIN     10
#define IN2_PIN     9
#define IN1_PIN     8
#define PWM_PIN     3

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

void setup() {
  // put your setup code here, to run once:
 
  pinMode(SLP_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);

  dc_motor3_clockwise();
  dc_motor3_set_speed(speed);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
