// Traffic Light Arduino Project by David Bertolino Jurek

#define LDR            A0

#define ORANGELIGHT     2
#define BLUELIGHT       3
#define REDLIGHT        8
#define YELLOWLIGHT     9
#define GREENLIGHT      10
#define PEDBUTTON       11

int valueLDR = 0;
bool light = false;
int pressed;

void setup() {
  pinMode(LDR, INPUT);
  pinMode(ORANGELIGHT, OUTPUT);
  pinMode(BLUELIGHT, OUTPUT);
  pinMode(REDLIGHT, OUTPUT);
  pinMode(YELLOWLIGHT, OUTPUT);
  pinMode(GREENLIGHT, OUTPUT);
  pinMode(PEDBUTTON, INPUT);
  Serial.begin(9600);
}

void stopWalker(){
  digitalWrite(BLUELIGHT, LOW);
  digitalWrite(ORANGELIGHT, HIGH);
}

void goWalker(){
  digitalWrite(BLUELIGHT, HIGH);
  digitalWrite(ORANGELIGHT, LOW);
}

void stopVehicle(int timer){
  digitalWrite(REDLIGHT, HIGH);
  digitalWrite(YELLOWLIGHT, LOW);
  digitalWrite(GREENLIGHT, LOW);
  goWalker();
  Serial.println("Bloqueado o trânsito de veículos e permitido a passagem de pedestres.");
  delay(timer*1000);
}

void waitVehicle(int timer){
  digitalWrite(REDLIGHT, LOW);
  digitalWrite(YELLOWLIGHT, HIGH);
  digitalWrite(GREENLIGHT, LOW);
  Serial.println("Atenção para mudanças de sinais!");
  delay(timer*1000);
}

void goVehicle(int timer){
  digitalWrite(REDLIGHT, LOW);
  digitalWrite(YELLOWLIGHT, LOW);
  digitalWrite(GREENLIGHT, HIGH);
  stopWalker();
  Serial.println("Permitido o trânsito de veículos e bloqueado a passagem de pedestres.");
  delay(timer*1000);
}

void stopTrafficLight(){
  digitalWrite(REDLIGHT, LOW);
  digitalWrite(YELLOWLIGHT, HIGH);
  digitalWrite(GREENLIGHT, LOW);
  digitalWrite(BLUELIGHT, LOW);
  digitalWrite(ORANGELIGHT, LOW);
  delay(1000);
  digitalWrite(YELLOWLIGHT, LOW);
}

void loop() {
  Serial.println(analogRead(LDR));
  delay(1000);
  
  pressed = digitalRead(PEDBUTTON);
  
  if(pressed == HIGH){
    goWalker();
    delay(15 * 1000);
    stopWalker();
    delay(2 * 1000);
  }
  else if(analogRead(LDR) < 500){
      stopTrafficLight();
  }
  else if(analogRead(LDR) >= 500) {
      stopVehicle(15);
      goVehicle(10);
      waitVehicle(2);
  }
}
