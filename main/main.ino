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

  analogWrite(enA, 1023);
  analogWrite(enB, 1023);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void turn_left(int forHowLong) {
  digitalWrite(in_A_1, HIGH);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, HIGH);
  digitalWrite(in_B_4, LOW);
  delay(forHowLong);
  stopCar();
}
void turn_right(int forHowLong) {
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, HIGH);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, HIGH);
  delay(forHowLong);
  stopCar();
}
void forward() {
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, HIGH);
  digitalWrite(in_B_3, HIGH);
  digitalWrite(in_B_4, LOW);
}

void backward() {
  digitalWrite(in_A_1, HIGH);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, HIGH);
}

void stopCar() {
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, LOW);

}
void breakdance() {
  int i = 0;
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  while (i != 5) {
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
int read_sensor() {
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

bool object(int grad) {
  servoSenor.write(grad);
  distance = read_sensor();
  if (distance <= 50) {
    return true;
  }
  return false;
}
int *moveTroughSensor (int start, int limit, int changer, int delayTime, bool downwards) {
  distance = read_sensor();
  int objectsGrad[10];
  int tempObjectsGrad[1];

  if (downwards) {
    for (int i = start; i >= limit; i += changer) {
      // Gjør at ting ser bedre ut ved å ikke ha delay på den første runden, det gjør at motoren ikke stopper men bare fortsetter
      if (i != start) {
        delay(delayTime);
      }
      if (object(i)) {
        if (not ((sizeof(objectsGrad) / sizeof(objectsGrad[0])) > 10)) {
          objectsGrad = tempObjectsGrad;
        }
      }
    }
  } else {
    for (int i = start; i <= limit; i += changer) {
      if (i != start) {
        delay(delayTime);
      }
      if (object(i)) {
        if (not ((sizeof(objectsGrad) / sizeof(objectsGrad[0])) > 10)) {
          objectsGrad[sizeof(objectsGrad) / sizeof(objectsGrad[0])] = i;
        }
      }
    }
  }
  return objectsGrad;
}

void loop() {
  // https://stackoverflow.com/questions/37538/how-do-i-determine-the-size-of-my-array-in-c
  int delayOnLoops = 125;
  int objects[] = {};
  moveTroughSensor(60, 130, 5, delayOnLoops, false);
  moveTroughSensor(130, 60, -5, delayOnLoops, true);
  turn_right(1000);

}
