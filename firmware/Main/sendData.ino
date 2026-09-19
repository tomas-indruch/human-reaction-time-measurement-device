void sendData(long time[], bool flags[], long start) {
  for (int i = 0; i < 8; i++) {
    // Vymaže předchozí hodnoty o stlačení tlačítek
    flags[i] = 0;

    // Vypočítá RD, kterou vloží do řetězce a následně odešle
    if (time[i]-start > 0){
      Serial.print(time[i]-start);
      Serial.print(",");
    }else {
      Serial.print(0);
      Serial.print(",");
    }
  }
  Serial.println("");
}