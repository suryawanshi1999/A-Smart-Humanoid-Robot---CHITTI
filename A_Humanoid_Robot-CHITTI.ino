//Coded By: Angelo Casimiro (4/27/14)
//Voice Activated Arduino (Bluetooth + Android)
//Feel free to modify it but remember to give credit
#include <SoftwareSerial.h>
#include<NewPing.h>
#include<Servo.h>
Servo r;
Servo l;
Servo h;
SoftwareSerial BT(11, 10); //TX, RX respetively
String voice;
const int IN1 = 29, IN2 = 13, IN3 = 8, IN4 = 9;
const int enable12 = 3 , enable34 = 2;
const int pingPin = 31; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 4;
long duration,cm,cm1=0;
int relay1=20;
int relay2=21;
NewPing sonar(31,4,200);
String voice1;

/***********/
int LED = 13; // Use the onboard Uno LED
//int isObstaclePin = 7;  // This is our input pin
//int isObstacle;  // HIGH MEANS NO OBSTACLE
/***********/
void setup() {
  r.attach(6);
  r.write(0);
  l.attach(7);
  l.write(90);
  h.attach(12);
  h.write(30);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(49,OUTPUT);
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
pinMode(pingPin,OUTPUT);
pinMode(echoPin,INPUT);
   
 brake();
 BT.begin(9600);
 Serial.begin(9600); 

  /******/
  pinMode(LED, OUTPUT);
  digitalWrite(relay1,LOW);
   digitalWrite(relay2,LOW);
  //pinMode(isObstaclePin, INPUT);
  /****/
}
//-----------------------------------------------------------------------//  
void loop() 
{
 
  //IR();
  cm=sonar.ping_cm();
  Serial.print(cm);
  if(cm==1)
  {
    digitalWrite(49,HIGH);
    for(int pos=30;pos<=90;pos+=1)
    {
      h.write(pos);
      delay(15);
    }



    
    digitalWrite(49,LOW);
    setup();
  }
  while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = BT.read(); //Conduct a serial read
  if (c == '#') {break;} //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  }  
  if (voice.length() > 0) {
    
    Serial.println(voice); 
    

 
  if(voice == "handshake") 
  {
 
   for(int pos=0;pos<=90;pos+=1)
   {
    r.write(pos);
    delay(15);
   }
   delay(3000);
   for(int pos=90;pos>=0;pos-=1)
   {
    r.write(pos);
    delay(15);
   }
   
  } 
  else if(voice=="left hand shake")
  {
    for(int pos=90;pos>=0;pos-=1)
    {
      l.write(pos);
      delay(15);
    }
    delay(3000);
    for(int pos=0;pos<=90;pos+=1)
    {
      l.write(pos);
      delay(15);
    }
  }
  else if(voice == "hands down") 
  {
    for(int pos=90;pos>=0;pos-=1)
    {
      r.write(pos);
      delay(15);
    }
  }
  else if(voice=="sleep")
  {
    digitalWrite(49,LOW);
    setup();
  }
  else if(voice == "move your head")
  {
    int d=0;
    h.write(0);
    while(d<4)
    {
      
     for(int pos=0;pos<=90;pos+=1)
   {
    h.write(pos);
    delay(15);
   }
    for(int pos=90;pos>=0;pos-=1)
    {
      h.write(pos);
      delay(15);
    }
    
    d=d+1;
  }
  h.write(30);
  }
  else if(voice == "dance")
  {int d=0;
  while(d<=4)
  {
    forward();
    for(int pos=0;pos<=90;pos+=1)
   {
    digitalWrite(49,HIGH);
    h.write(pos);
    l.write(pos);
    r.write(pos);
    delay(15);
   }
   backward();
   for(int pos=90;pos>=0;pos-=1)
   {
    digitalWrite(49,LOW);
    h.write(pos);
    l.write(pos);
    r.write(pos);
    delay(15);
   }
   d=d+1;
   
   
  }
  setup();
   
  }
  else if(voice == "move forward")
  {
    forward();
  }
  else if(voice == "move backward")
  {
    backward();
  }
  else if(voice =="move left")
  {
    left();
  }
  else if(voice =="move right")
  {
    right();
  } 
  else if(voice =="stop")
  {
    brake();
  }
  else if(voice =="happy")
  {
    digitalWrite(49,HIGH);
  }
  else if(voice =="Jai Mata Di")
  {
    for(int pos=0;pos<=180;pos+=1)
    {
      l.write(pos);
      r.write(pos);
      delay(15);
    }
    for(int pos=180;pos>=0;pos-=1)
    {
      l.write(pos);
      r.write(pos);
      delay(15);
    }
    setup();
    }
  else if(voice =="light on")
  {
    digitalWrite(relay1,HIGH);
    delay(1000);
   digitalWrite(relay1,LOW);
  }
  else if(voice =="fan on")
  {
    digitalWrite(relay2,HIGH);
    delay(1000);
    digitalWrite(relay2,LOW);
  }



voice="";
}} 
void forward()
{


    digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}
void backward()
{
   digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void brake()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
/*void IR()
{
  isObstacle = digitalRead(isObstaclePin);
  if (isObstacle == HIGH)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(LED, HIGH);
  }
  else
  {
    Serial.println("clear");
    digitalWrite(LED, LOW);
  }
  delay(800);
}*/
