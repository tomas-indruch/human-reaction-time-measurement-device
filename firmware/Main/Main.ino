const int buttons[] = {15, 16, 17, 18, 8, 9, 10, 11}; // Tlačítka přiřazeny k pinům
bool flags[] = {0, 0, 0, 0, 0, 0, 0, 0}; // Indexy, zda již bylo tlačítko stisknuto
long time[] = {0, 0, 0, 0, 0, 0, 0, 0}; // Naměřené hodnoty RD
const int leds[] = {2, 3, 4, 5};  // LED diody přiřazeny k pinům
const int buzzer = 6; // Bzučák přiřazen na pin
long start; // Referenční hodnota počátku měření

// Nastavení počátečních podmínek 
int colour = 3;
int frequency = 0;
int stay = 4000;
int variability = 0;

void setup() {
  // Zahájení sériové komunikace
  Serial.begin(9600);
  Serial.setTimeout(10);

  // Nastavení vstupů a výstupů Arduina
  pinMode(buzzer, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }

  for (int i = 0; i < 8; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {
  // Počátek měření, kdy se zapne stimul a zaznamená referenční hodnota
  start = millis();
  digitalWrite(leds[colour], HIGH);
  tone(buzzer, frequency, 3000);

  // Kontrola stisknutí tlačítek a zapisování časů stisknutí
  while (millis()-start < 3000){
    for (int i = 0; i < 8; i++){
      if (flags[i] == 0 && !digitalRead(buttons[i])){
        time[i] = millis();
        flags[i] = 1;
      }
    }
  }

  // Ukončení stimulu a odeslání dat
  digitalWrite(leds[colour], LOW);
  sendData(time, flags, start);
  
  // Prodleva mezi měřeními
  randomSeed(analogRead(0));
  delay(stay + random(variability));

  // Kontrola nových příchozích dat
  if (Serial.available() > 0)
  {
    getValues();
  }
}