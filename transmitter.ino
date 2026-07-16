/*
 * LoRa Based Coal Mine Safety Monitoring & Security System Using Rover
 * Transmitter Node
 * Developed by: Vishnu V
 */

#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// ---------------- Blynk ----------------
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
char ssid[] = "SAFETY";
char pass[] = "11223344";

// ---------------- DHT ----------------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---------------- Sensors ----------------
#define GAS_SENSOR 36
#define MEMS_SENSOR 39

#define TRIG_PIN 32
#define ECHO_PIN 33

// ---------------- Motor Driver ----------------
#define IN1 13
#define IN2 12
#define IN3 27
#define IN4 25

// ---------------- LoRa ----------------
#define SS_PIN 5
#define RST_PIN 14
#define DIO0_PIN 26

long duration;
float distance;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(GAS_SENSOR, INPUT);
  pinMode(MEMS_SENSOR, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  Blynk.config(auth);
  Blynk.connect();

  SPI.begin();

  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  if (!LoRa.begin(433E6))
  {
    Serial.println("LoRa Initialization Failed!");
    while (1);
  }

  Serial.println("LoRa Started Successfully");
}
