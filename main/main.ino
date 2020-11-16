//henter biblioteket "servo.h"
#include <Servo.h>

Servo servoSenor;

//rasberrypi input
int rasp_1 = 4;
int rasp_1_state;

<<<<<<< HEAD
=======
int rasp_1 = 4;
int rasp_1_state;
>>>>>>> parent of 7520955... reverted to 0.93
// Motor a
int enA = 13;
int in_A_1 = 12;
int in_A_2 = 11;

// Motor b
int enB = 10;
int in_B_3 = 9;
int in_B_4 = 8;

// Sensor
int trigPin = 6;
int echoPin = 7;
<<<<<<< HEAD
long duration; 
int distance;  

int thresHold = 25;

//bestemmer hva de ulike pins'ene gjør 
=======
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement

int thresHold = 25;

>>>>>>> parent of 7520955... reverted to 0.93
void setup()
{
  servoSenor.attach(5);
  servoSenor.write(0);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in_A_1, OUTPUT);
  pinMode(in_A_2, OUTPUT);
  pinMode(in_B_3, OUTPUT);
  pinMode(in_B_4, OUTPUT);
  pinMode(rasp_1, INPUT);
<<<<<<< HEAD
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  analogWrite(enA, 225);
  analogWrite(enB, 225);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
  Serial.println("Hello, running: V.0.96");
}
//svinger til venstre
=======

  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  analogWrite(enA, 225);
  analogWrite(enB, 225);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Hello, running: V.0.95");
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
>>>>>>> parent of 7520955... reverted to 0.93
void turn_left(int forHowLong)
{
  digitalWrite(in_A_1, HIGH);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, HIGH);
  digitalWrite(in_B_4, LOW);
  delay(forHowLong);
  stopCar();
}
<<<<<<< HEAD
//svinger til høyre
=======
>>>>>>> parent of 7520955... reverted to 0.93
void turn_right(int forHowLong)
{
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, HIGH);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, HIGH);
  delay(forHowLong);
  stopCar();
}
<<<<<<< HEAD
//kjører rett frem
=======
>>>>>>> parent of 7520955... reverted to 0.93
void forward()
{
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, HIGH);
  digitalWrite(in_B_3, HIGH);
  digitalWrite(in_B_4, LOW);
}
<<<<<<< HEAD
//kjører bakover/rygger
=======

>>>>>>> parent of 7520955... reverted to 0.93
void backward()
{
  digitalWrite(in_A_1, HIGH);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, HIGH);
}
<<<<<<< HEAD
//stopper bilen helt
=======

>>>>>>> parent of 7520955... reverted to 0.93
void stopCar()
{
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, LOW);
}

void breakdance()
{
  int i = 0;
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  while (i != 5)
  {
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
<<<<<<< HEAD
//får servoen til å bevege seg og får sensoren til å lese avsstanden
=======

>>>>>>> parent of 7520955... reverted to 0.93
void turnDegrees(int degree)
{
  servoSenor.write(degree);
  Serial.println(degree);
<<<<<<< HEAD
  //svinger bilen til ditt hvor det er lengst avstand til en hindring 
=======

>>>>>>> parent of 7520955... reverted to 0.93
  if (degree > 90)
  {
    turn_left((90 + degree) * 3.3);
  }
  else
  {
    turn_right((90 - degree) * 3.3);
  }
<<<<<<< HEAD
}
//leser av sensoren
=======
  // TODO
}
>>>>>>> parent of 7520955... reverted to 0.93
int read_sensor()
{
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
<<<<<<< HEAD
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
=======
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
>>>>>>> parent of 7520955... reverted to 0.93
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
<<<<<<< HEAD
//får bilen til å stoppe hvis sensoren oppdager noe forran seg
=======

>>>>>>> parent of 7520955... reverted to 0.93
bool object(int grad)
{
  servoSenor.write(grad);
  distance = read_sensor();
  if (distance <= thresHold)
  {
    return true;
  }
  return false;
}

bool objectCurrent()
{
  distance = read_sensor();
  Serial.println(distance <= thresHold);
  if (distance <= thresHold)
  {
    return true;
  }
  return false;
}
<<<<<<< HEAD
//finner den graden hvor det er lengst til nærmeste hindring og returnere graden (finner beste løsning)
=======

>>>>>>> parent of 7520955... reverted to 0.93
int findBestSolution(int start, int limit, int changer, int delayTime, bool downwards)
{
  distance = read_sensor();
  int besteGRAD = 0;
  int besteDISTANCE = 0;

  if (downwards)
  {
    for (int i = start; i >= limit; i += changer)
    {
      // Gjør at ting ser bedre ut ved å ikke ha delay på den første runden, det gjør at motoren ikke stopper men bare fortsetter
      if (i != start)
      {
        delay(delayTime);
      }
      if (not object(i))
      {
        if (besteDISTANCE < read_sensor())
        {
          besteDISTANCE = read_sensor();
          besteGRAD = i;
          Serial.println(besteGRAD);
          Serial.println(besteDISTANCE);
        }
      }
    }
  }
  else
  {
    for (int i = start; i <= limit; i += changer)
    {
      if (i != start)
      {
        delay(delayTime);
      }
      if (not object(i))
      {
        if (besteDISTANCE < read_sensor())
        {
          besteDISTANCE = read_sensor();
          besteGRAD = i;
          Serial.println(besteGRAD);
          Serial.println(besteDISTANCE);
        }
      }
    }
  }
  return besteGRAD;
}
<<<<<<< HEAD
bool object_while_moving(int grad, int andre_grad) {
  delay(100);
  for (int i = grad; i <= andre_grad; i += 1){
    servoSenor.write(i);
  }
  distance = read_sensor();
  if (distance <= thresHold) {
=======
int andre_grad;
int i = 0;
bool object(int grad, int andre_grad)
{
  for (int i = grad; i <= andre_grad; i += 1)
  {
    servoSenor.write(i);
  }
  distance = read_sensor();
  if (distance <= thresHold)
  {
>>>>>>> parent of 7520955... reverted to 0.93
    return true;
  }
  return false;
}
<<<<<<< HEAD

//får sensoren til å gå frem å tilbake mens den kjører, og bilen til å stoppe hvis sensoren ser noe
void loop()
{
  bool objectAhead;
  int i = 10;
  while(!objectAhead){
    if (i >= 150){
      if (object(i)){
            objectAhead = true;
      }
    }else{
      i = 0;
    }
    i += 1;
    Serial.println("i");
    Serial.println(i);
    forward();
  }
  stopCar();
  int delayOnLoops = 150;
        int solution = findBestSolution(10, 170, 10, delayOnLoops, false);
      turnDegrees(solution);
=======
void loop()
{
  rasp_1_state = digitalRead(rasp_1);
  // Show the state of pushbutton on serial monitor
  Serial.println(digitalRead(rasp_1));
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (rasp_1_state == HIGH) {
    int delayOnLoops = 150;
    if (object(80, 100))
    {
      stopCar();
      int solution = findBestSolution(10, 170, 10, delayOnLoops, false);
      turnDegrees(solution);
    }
    else
    {
      Serial.println(false);
      forward();
    }
  }
  else {

  }
>>>>>>> parent of 7520955... reverted to 0.93
}
