#include <SPI.h>
#include<Servo.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // declaration CE, CSN for setting nRF24L01 radio in SPI bus
const byte address[6] = "00001"; // transmitter and receiver should have same adress

Servo throttle;
Servo elevator;
Servo aileron;
Servo Rudder;
Servo mode;

#define echoPin 22 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 23 //attach pin D3 Arduino to pin Trig of HC-SR04

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW); // set power level (minimum when modules are close)
// RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX
// (high level) recommend to use GND, 3.3v bypass capacitor to have stable voltage while it works
  radio.startListening(); // set module as receiver
  
  throttle.attach(2);
  elevator.attach(3);
  aileron.attach(4);
  Rudder.attach(5);
  mode.attach(6);

  mode.write(60);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

void ready(){
  throttle.write(45);
  elevator.write(140);
  aileron.write(140);
  Rudder.write(45);
  delay(2000);
  throttle.write(95);
  elevator.write(110);
  aileron.write(95);
  Rudder.write(85);
}

void land(){
    throttle.write(70);
}

void take_off(){
  for(int i=95; i<=130; i+=10){
      throttle.write(i);
  }
}

void forward(){
  elevator.write(110);
}

void backward(){
  elevator.write(80);
}

void left(){
  aileron.write(80);
}

void right(){
  aileron.write(110);
}

void hover(){
  throttle.write(95);
  elevator.write(110);
  aileron.write(95);
  Rudder.write(85);
}


void loop() {
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  // Reads the echoPin, returns the sound wave travel time in microseconds
//  duration = pulseIn(echoPin, HIGH);
//  // Calculating the distance
//  distance = duration * 0.034 / 2;
//  
//  Serial.println(distance);
  
  
  if (radio.available()) {
    int number = number;
    radio.read(&number,number);
    Serial.println(number);
    if (number==4){
      ready();
//      Serial.println("READY");
    }
    else if (number==6){
        take_off();
        delay(6000);
        hover();
//        Serial.println("Take off");
      }

    else if(number==7){
      land();
//      Serial.println("landing");
    }
    else if(number==8){
      throttle.write(45);
      delay(5000);
    }
  }
}
