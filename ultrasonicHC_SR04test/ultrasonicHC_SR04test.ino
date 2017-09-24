
const int trigPin = 12;
const int echoPin = 13;
long duration;
int distanceCm, distanceInch;
void setup() {
  Serial.begin(57600);
  while(!Serial){
    ;
  }
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  while(!Serial.available());
  if(Serial.read() == 'a')
  {
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
  }
}


