int incomingByte = 0;
int pinTrig = 4;
int pinEcho = 3;
char dir = 'S';
long temps;
float distance;

void setup() {
  Serial.begin(9600);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  digitalWrite(pinTrig, LOW);  
}

void loop() {
  digitalWrite(pinTrig, HIGH);        
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  temps = pulseIn(pinEcho, HIGH);
  if (temps > 30000) {              
    //Serial.println("Echec de la mesure");
    dir = 'S';
  }

  else {
    temps = temps/2;
    distance = (temps*340)/10000.0;                  
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
      
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 71) {
      dir = 'G';
      //Serial.println("a gauche");
    }
    else if (incomingByte == 68) {
      dir = 'D';
      //Serial.println("a droite");
    }
    else if (incomingByte == 65) {
      //Serial.println("tout droite");
      dir = 'A';
    }
    else {
      //Serial.print("Aucune valeur");
      dir = 'S';
    }

  if (distance < 10) {
    //Serial.print("Trop proche");
    dir = 'S';
  }

  if (distance > 300) {
    Serial.print("Trop loin");
    //dir = 'S';
  }

  Serial.print(dir);
  }
}
