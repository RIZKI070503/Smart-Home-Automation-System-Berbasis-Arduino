// Smart Home Automation System Source Code
#include <DHT.h>

#define DHTPIN 2 // Pin untuk sensor DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define RELAY_PIN 3 // Relay untuk perangkat rumah tangga
#define LED_PIN 4   // Indikator LED

#include <SoftwareSerial.h>
SoftwareSerial bluetooth(10, 11); // RX, TX untuk HC-05

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  bluetooth.begin(9600);
  Serial.begin(9600);
  dht.begin();
  Serial.println("Smart Home Automation System Started");
}

void loop() {
  if (bluetooth.available()) {
    char command = bluetooth.read();
    handleCommand(command);
  }

  // Mengukur suhu dan kelembapan
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Mengirim data ke smartphone
  if (!isnan(temperature) && !isnan(humidity)) {
    bluetooth.print("Temp: ");
    bluetooth.print(temperature);
    bluetooth.print(" C, Humidity: ");
    bluetooth.print(humidity);
    bluetooth.println(" %");
  }
  delay(2000); // Delay untuk pembaruan data
}

void handleCommand(char command) {
  switch (command) {
    case '1': // Menyalakan perangkat
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
      Serial.println("Perangkat ON");
      bluetooth.println("Perangkat ON");
      break;
    case '0': // Mematikan perangkat
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
      Serial.println("Perangkat OFF");
      bluetooth.println("Perangkat OFF");
      break;
    default:
      Serial.println("Command tidak dikenal");
      bluetooth.println("Command tidak dikenal");
      break;
  }
}
