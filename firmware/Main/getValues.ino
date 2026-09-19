void getValues() {
  // Načtení řetězce do proměnné str
  String str = Serial.readStringUntil('\n');

  // Prealokace paměti
  String newValues[5];
  int valueIndex = 0;
  String currentValue = "";

  // Přijme první čtyři hodnoty ze str a uloží je do proměnné newValues
  for (int i = 0; i < str.length(); i++) {
    char currentChar = str.charAt(i);

    if (currentChar != ',') {
      currentValue += currentChar;
    } else {
      newValues[valueIndex] = currentValue;
      valueIndex++;
      currentValue = "";
    }

    if (valueIndex >= 4) {
      break;
    }
  }

  // Přiřadí index požadované barvě diody
  if (newValues[0] == "Red")
  {
    colour = 0;
  }else if (newValues[0] == "Blue")
  {
    colour = 1;
  }else if (newValues[0] == "Green")
  {
    colour = 2;
  }else if (newValues[0] == "Yellow")
  {
    colour = 3;
  }else
  {
    colour = 4;
  }

  // Přiřadí nové hodnoty frekvenci a statické a dynamické prodlevě
  frequency = newValues[1].toInt();
  stay = newValues[2].toInt();
  variability = newValues[3].toInt();

  // Vrátí nové hodnoty do hlavní funkce
  return colour;
  return frequency;
  return stay;
  return variability;
}