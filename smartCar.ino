#include <Servo.h>
Servo myservo;  // create servo object to control a servo
#define servoPin 16
#define sensorPin 15
#define ENA    11
#define N1     12
#define N2     13 
#define ENB     3
#define N3      2
#define N4      18
byte geschwindigkeit;                        // Die aktuelle Geschwindigkeit
byte korrekturBewegungProzent;               // Stärke der Korrektur in Prozent
bool korrekturBewegungRichtung;              // true = links, false = rechts
bool sensorikRichtung = true;                // Momentane Drehrichtung des Servos, true = links, false = rechts
byte sensorikPosition = 0;                   // Sensor-Position, 0 = rechts, 180 = links
unsigned long sensorikVerzoegerung;          // Verzögerung für Schwenkung und Messung der Sensorik

float sensorWert;                            // Momentaner Sensor-Wert
float refSpannung = 4.96;                    // Korrektur für Sensor von 2A
const float sensorMin = 512;                 // Sensor-Wert bei freiem Feld
const float sensorMax = 2048;                // Gewünschter Maximalwert des Sensors

void setup() {
  Serial.begin(9600);         /* DEV */
  
  myservo.attach(servoPin);
  myservo.write(sensorikPosition);

  pinMode(sensorPin, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(N1, OUTPUT);
  pinMode(N2, OUTPUT);
  pinMode(N3, OUTPUT);
  pinMode(N4, OUTPUT);
    
  pinMode(ENA, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  gehirn();
  analogWrite(ENA, geschwindigkeit);        /* DEV */
  analogWrite(ENB, geschwindigkeit);        /* DEV */  
  digitalWrite(N1, LOW);                    /* DEV */ 
  digitalWrite (N2, HIGH);                  /* DEV */ 
  digitalWrite (N3, HIGH);                  /* DEV */ 
  digitalWrite (N4, LOW);                   /* DEV */ 
  
}

//  Sensorik-Routine
//  ----------------

void sensorikInfrarot() {
  if (sensorikVerzoegerung < millis()) {  // Verzögerung für Schwenkung und Messung
    if (sensorikRichtung) {               // 
      sensorikPosition++;        
    }
    else {
      sensorikPosition--;
    }
    myservo.write(sensorikPosition);
    if (sensorikPosition >= 180 || sensorikPosition <= 0) {
        sensorikRichtung = !sensorikRichtung;
    }
    sensorikVerzoegerung = millis()+5;    // 5ms Verzögerung für Servo
    sensorWert = analogRead(sensorPin)*refSpannung;
    Serial.println(sensorWert);               /* DEV */
    Serial.println(geschwindigkeit);          /* DEV */
  }
}


//  Bewegungsfunktionen:
//  --------------------

void bewegungFahrt(bool richtungFahrt) {          // richtungFahrt: geradeaus = true; rückwärts = false, geschwindigkeit in Prozent

}

void bewegungKurve(bool richtungKurve, byte einschlagKurve) {            // richtungKurve: links = true, rechts = false; einschlag gibt die Kurvenstärke in Prozent an

}

void bewegungAntrieb(bool rad, bool drehrichtungAntrieb, byte geschwindigkeitAntrieb) {      // Subroutine - Grundlegender Antrieb eines Rads, rad: links = true, rechts = false; drehrichtungAntrieb: vorwärts = true, rückwärts = false; geschwindigkeitAntrieb in Prozent
  
}

//  Entscheidungsroutinen:
//  ----------------------

void gehirn() {
  sensorikInfrarot();  
  int sensorInt = map(sensorWert, sensorMin, sensorMax, 0, 4);
  switch (sensorInt) {
    case 0:
      geschwindigkeit = 80;
      break;
    case 1:
      geschwindigkeit = 40;
      break;
    case 2:
      geschwindigkeit = 20;
      break;      
    case 3:
      geschwindigkeit = 0;
      break; 
    default:
      break;  
  }
}
