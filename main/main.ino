int enA = 13;
int in_A_1 = 12;
int in_A_2 = 11;
int trigPin = 6;
int echoPin = 7;

int enB = 10;
int in_B_3 = 9;
int in_B_4 = 8;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  Serial.print("Hello");
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in_A_1, OUTPUT);
  pinMode(in_A_2, OUTPUT);
  pinMode(in_B_3, OUTPUT);
  pinMode(in_B_4, OUTPUT);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void turn_left() {
  digitalWrite(in_A_1, HIGH);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, HIGH);
  digitalWrite(in_B_4, LOW);
  delay(300);
}
void turn_right() {
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, HIGH);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, HIGH);
  delay(300);
}
void forward() {
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, HIGH);
  digitalWrite(in_B_3, HIGH);
  digitalWrite(in_B_4, LOW);
  delay(500);
}
void backward() {
  digitalWrite(in_A_1, HIGH);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, HIGH);
  delay(500);
}
void breakdance() {
  int i = 0;
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  while (i != 5){
    digitalWrite(in_A_1, HIGH);
    digitalWrite(in_A_2, LOW);
    digitalWrite(in_B_3, HIGH);
    digitalWrite(in_B_4, LOW);
    delay(200);  
    digitalWrite(in_A_1, LOW);
    digitalWrite(in_A_2, HIGH);
    digitalWrite(in_B_3, LOW);
    digitalWrite(in_B_4, HIGH);
    delay(200);
    digitalWrite(in_A_1, LOW);
    digitalWrite(in_A_2, HIGH);
    digitalWrite(in_B_3, LOW);
    digitalWrite(in_B_4, HIGH);
    delay(1000);
    digitalWrite(in_A_1, LOW);
    digitalWrite(in_A_2, HIGH);
    digitalWrite(in_B_3, HIGH);
    digitalWrite(in_B_4, LOW);
    delay(75);
    digitalWrite(in_A_1, HIGH);
    digitalWrite(in_A_2, LOW);
    digitalWrite(in_B_3, LOW);
    digitalWrite(in_B_4, HIGH);
    delay(75);
    i += 1;
  }
}
 
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delay(.002);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delay(.01);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
    Serial.print(distance);
  Serial.println(" cm");
  if (distance < 20){
    backward();
    delay(75);
    turn_left();
  }
  else{
    forward();
  }
}
