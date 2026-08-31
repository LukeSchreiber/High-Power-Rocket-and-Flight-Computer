#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <FS.h>
#include <LittleFS.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define BME280_ADDRESS 0x76

#define LOG_INTERVAL_MS 50      // ~20Hz
#define FLUSH_INTERVAL_MS 1000  // flush to flash every 1s
#define BASELINE_SAMPLES 10

Adafruit_BME280 bme;
File logFile;
char logPath[32];

float groundPressure = 0;
unsigned long startTime = 0;
unsigned long lastLog = 0;
unsigned long lastFlush = 0;
bool logging = false;

// ---------- flight file naming ----------
int nextFlightNumber() {
  int maxNum = 0;
  File root = LittleFS.open("/");
  File f = root.openNextFile();
  while (f) {
    int n;
    if (sscanf(f.name(), "flight_%d.csv", &n) == 1) {
      if (n > maxNum) maxNum = n;
    }
    f = root.openNextFile();
  }
  return maxNum + 1;
}

// ---------- serial commands ----------
void listFiles() {
  Serial.println("--- FILES ---");
  File root = LittleFS.open("/");
  File f = root.openNextFile();
  while (f) {
    Serial.printf("%s  (%u bytes)\n", f.name(), f.size());
    f = root.openNextFile();
  }
  Serial.printf("Used: %u / %u bytes\n", LittleFS.usedBytes(), LittleFS.totalBytes());
  Serial.println("--- END ---");
}

void dumpAll() {
  File root = LittleFS.open("/");
  File f = root.openNextFile();
  while (f) {
    Serial.printf("===== BEGIN %s =====\n", f.name());
    while (f.available()) Serial.write(f.read());
    Serial.printf("\n===== END %s =====\n", f.name());
    f = root.openNextFile();
  }
}

void wipeAll() {
  if (logging) { logFile.close(); logging = false; }
  File root = LittleFS.open("/");
  File f = root.openNextFile();
  while (f) {
    String path = String("/") + f.name();
    f = root.openNextFile();
    LittleFS.remove(path);
  }
  Serial.println("All logs erased. Reset board to start a new flight.");
}

void handleSerial() {
  if (!Serial.available()) return;
  char c = Serial.read();
  if (c == 'd' || c == 'D') { dumpAll(); }
  else if (c == 'l' || c == 'L') { listFiles(); }
  else if (c == 'w' || c == 'W') { wipeAll(); }
  else if (c == 's' || c == 'S') {
    logging = !logging;
    Serial.println(logging ? "Logging RESUMED" : "Logging PAUSED");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(SDA_PIN, SCL_PIN);
  if (!bme.begin(BME280_ADDRESS, &Wire)) {
    Serial.println("BME280 not found at 0x76. Check wiring.");
    while (1) delay(10);
  }
  Serial.println("BME280 OK");

  // max sampling, IIR filter off for fast response
  bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                  Adafruit_BME280::SAMPLING_X2,   // temperature
                  Adafruit_BME280::SAMPLING_X16,  // pressure
                  Adafruit_BME280::SAMPLING_NONE, // humidity off
                  Adafruit_BME280::FILTER_X4,
                  Adafruit_BME280::STANDBY_MS_0_5);

  if (!LittleFS.begin(true)) {   // true = format if mount fails
    Serial.println("LittleFS mount failed.");
    while (1) delay(10);
  }
  Serial.println("LittleFS mounted");
  listFiles();

  // ground baseline
  Serial.println("Averaging ground baseline, hold still...");
  float sum = 0;
  for (int i = 0; i < BASELINE_SAMPLES; i++) {
    sum += bme.readPressure() / 100.0F;
    delay(100);
  }
  groundPressure = sum / BASELINE_SAMPLES;
  Serial.printf("Ground pressure: %.2f hPa\n", groundPressure);

  snprintf(logPath, sizeof(logPath), "/flight_%d.csv", nextFlightNumber());
  logFile = LittleFS.open(logPath, FILE_WRITE);
  if (!logFile) {
    Serial.println("Failed to open log file!");
    while (1) delay(10);
  }
  logFile.printf("# ground_pressure_hPa,%.2f\n", groundPressure);
  logFile.println("time_ms,pressure_hPa,temperature_C,altitude_m");
  logFile.flush();

  Serial.printf("Logging to %s\n", logPath);
  Serial.println("Commands: L=list  D=dump  W=wipe  S=start/stop");

  startTime = millis();
  lastFlush = millis();
  logging = true;
}

void loop() {
  handleSerial();

  unsigned long now = millis();
  if (logging && now - lastLog >= LOG_INTERVAL_MS) {
    lastLog = now;

    float pressure = bme.readPressure() / 100.0F;
    float temperature = bme.readTemperature();
    float altitude = 44330.0 * (1.0 - pow(pressure / groundPressure, 0.1903));

    logFile.printf("%lu,%.2f,%.2f,%.2f\n", now - startTime, pressure, temperature, altitude);

    if (now - lastFlush >= FLUSH_INTERVAL_MS) {
      logFile.flush();
      lastFlush = now;
    }
  }
}