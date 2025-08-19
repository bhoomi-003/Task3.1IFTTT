#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

bool initBH1750() {
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23)) {
    Serial.println("BH1750 ready at 0x23");
    return true;
  }
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5C)) {
    Serial.println("BH1750 ready at 0x5C");
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();
  // Optional: slow the bus a bit if wiring is long/noisy
  // Wire.setClock(100000); // 100 kHz

  if (!initBH1750()) {
    Serial.println("BH1750 not detected. Check wiring & address (0x23/0x5C).");
    while (1);
  }
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.println(lux);  // just the number, perfect for Node-RED
  delay(3000);
}
