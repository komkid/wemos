/* DHT Shield - Simple
 *
 * Example testing sketch for various DHT humidity/temperature sensors
 * Written by ladyada, public domain
 *
 * Depends on Adafruit DHT Arduino library
 * https://github.com/adafruit/DHT-sensor-library
 */

#include "DHT.h"

#define DHTPIN D4     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

const int relayPin = D1;
const long interval = 5 * 60 * 1000;  // pause for two seconds

#include "Timer.h"
Timer t;
int dhtEvent;

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // turn on relay with voltage HIGH
  
  Serial.begin(9600);
  Serial.print("Check every ");
  Serial.print(interval);
  Serial.println(" millisec.");

  dhtEvent = t.every(interval, dhtRead);
  Serial.print("DHT event started id=");
  Serial.println(dhtEvent);

  dht.begin();
}

void loop() {
  t.update();
}

void dhtRead() {
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float temp = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" *C ");
  
  if (temp > 28) {
    digitalWrite(relayPin, HIGH); // turn on relay with voltage HIGH
  } else {
    digitalWrite(relayPin, LOW);  // turn off relay with voltage LOW
  }

}
