//henter biblioteket "servo.h"
#include <Servo.h>

Servo servoSenor;

//rasberrypi input
int rasp_1 = 4;
int rasp_1_state;

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
long duration; 
int distance;  

int thresHold = 25;

//bestemmer hva de ulike pins'ene gjør 
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
void turn_left(int forHowLong)
{
  digitalWrite(in_A_1, HIGH);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, HIGH);
  digitalWrite(in_B_4, LOW);
  delay(forHowLong);
  stopCar();
}
//svinger til høyre
void turn_right(int forHowLong)
{
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, HIGH);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, HIGH);
  delay(forHowLong);
  stopCar();
}
//kjører rett frem
void forward()
{
  digitalWrite(in_A_1, LOW);
  digitalWrite(in_A_2, HIGH);
  digitalWrite(in_B_3, HIGH);
  digitalWrite(in_B_4, LOW);
}
//kjører bakover/rygger
void backward()
{
  digitalWrite(in_A_1, HIGH);
  digitalWrite(in_A_2, LOW);
  digitalWrite(in_B_3, LOW);
  digitalWrite(in_B_4, HIGH);
}
//stopper bilen helt
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
//får servoen til å bevege seg og får sensoren til å lese avsstanden
void turnDegrees(int degree)
{
  servoSenor.write(degree);
  Serial.println(degree);
  //svinger bilen til ditt hvor det er lengst avstand til en hindring 
  if (degree > 90)
  {
    turn_left((90 + degree) * 3.3);
  }
  else
  {
    turn_right((90 - degree) * 3.3);
  }
}
//leser av sensoren
int read_sensor()
{
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
//får bilen til å stoppe hvis sensoren oppdager noe forran seg
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
//finner den graden hvor det er lengst til nærmeste hindring og returnere graden (finner beste løsning)
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
bool object_while_moving(int grad, int andre_grad) {
  delay(100);
  for (int i = grad; i <= andre_grad; i += 1){
    servoSenor.write(i);
  }
  distance = read_sensor();
  if (distance <= thresHold) {
    return true;
  }
  return false;
}

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
}
