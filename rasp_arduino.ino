#include <SoftwareSerial.h>

SoftwareSerial rasp(9,10);

void setup() {
  Serial.begin(9600);
  rasp.begin(9600);
}

void loop() {
  if(rasp.available()>0) {
    String b=rasp.readStringUntil(' ');
    String a=rasp.readStringUntil('\n');
    int x=0,y=0;
    for(int i=0;a[i]!='\0';i++) {
      x*=10;
      x+=(a[i]-48);
    }
    for(int i=0;b[i]!='\0';i++) {
      y*=10;
      y+=(b[i]-48);
    }
    
    if(x>230) {
      rasp.println("Right");
    }
    else if(x<190) {
      rasp.println("Left");
    }
    else if(y<290) {
      rasp.println("Forward");
    }
    else if(y>330) {
      rasp.println("Back");
    }
    else {
      rasp.println("Down");
    }
    
    rasp.print("x: ");
    rasp.print(x);
    rasp.print(" , y: ");
    rasp.println(y);
  }
}
