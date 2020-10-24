#include <Servo.h>


Servo servoSenor;

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
int lastDistance;

void setup() {
  servoSenor.attach(5);
  servoSenor.write(0);
  Serial.print("Hello");
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in_A_1, OUTPUT);
  pinMode(in_A_2, OUTPUT);
  pinMode(in_B_3, OUTPUT);
  pinMode(in_B_4, OUTPUT);

  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

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
  delay(50);
}

void backward() {
  digitalWrite(in_A_1, HIGH);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, HIGH);
  delay(500);
}

void stopCar(){
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, LOW);
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
int read_sensor(){
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void loop() {
  int best_distance = 0;
  for (int i = 60; i <= 130; i= i+5){
    servoSenor.write(i);
    delay(25);
    distance = read_sensor();
    distance = read_sensor();
    if (distance < 50 or (lastDistance < 100 and distance > 500) ){
      stopCar();
        for (int i = 10; i <= 170; i= i+5){
        distance = read_sensor();
        servoSenor.write(i);
        distance = read_sensor();
        if (distance > best_distance){
          best_distance = distance;
        }
        }
      }
      if (best_distance < 90){
        turn_left();
      }
      else if (best_distance > 90){
        turn_right();
      }
    else{
      forward();
      lastDistance = distance;
    }
  }

for (int i = 130; i >= 60; i = i-5){
  servoSenor.write(i);
  delay(25);
  distance = read_sensor();
  distance = read_sensor();
  if (distance < 50 or (lastDistance < 100 and distance > 500) ){
    stopCar();
    int grad = 0;
    int gradDistance = 0;
    for (int i = 170; i >= 170; i= i-5){
      distance = read_sensor();
      servoSenor.write(i);
      distance = read_sensor();
      if (distance > best_distance){
        best_distance = distance;
      }
    }
  }
  if (best_distance < 90){
    turn_left();
  }
  else if (best_distance > 90){
    turn_right();
  }
  else{
    forward();
    lastDistance = distance;
  }
}

}

