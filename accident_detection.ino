#include <Wire.h>
#include <math.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); // RX, TX for Bluetooth

const int MPU_ADDR = 0x68;
const int vibPin = 2;
const int buzzer = 7;
const int redLED = 8;
const int greenLED = 9;
const int cancelButton = 6; // SOS Cancel Button

int16_t AcX, AcY, AcZ;
float pitch, roll;
int alarmState = 0;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  Wire.begin();

  pinMode(vibPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(cancelButton, INPUT_PULLUP);

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.println("Tilt-based Accident Detector Initialized...");
  BT.println("Accident Detector Ready");
}

void loop() {

  // Read vibration sensor
  int vib = digitalRead(vibPin);

  // Read MPU6050 acceleration data
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU_ADDR, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  // Calculate pitch and roll
  pitch = atan2(
    AcY,
    sqrt(pow(AcX, 2) + pow(AcZ, 2))
  ) * 180.0 / PI;

  roll = atan2(-AcX, AcZ) * 180.0 / PI;

  // Accident detection conditions
  bool tiltTrigger =
    (abs(pitch) > 45 || abs(roll) > 45);

  bool vibTrigger =
    (vib == HIGH);

  if (
    tiltTrigger ||
    (vibTrigger && (abs(pitch) > 30 || abs(roll) > 30))
  ) {

    alarmState = 1;

    // Activate accident indicators
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenLED, LOW);

    // Send accident alert
    BT.println("⚠️ Accident Detected!");
    Serial.println("⚠️ Accident Detected!");

    bool cancelPressed = false;

    unsigned long startTime = millis();

    BT.println(
      "Press SOS Cancel Button to abort alert (5s window)"
    );

    Serial.println(
      "Press SOS Cancel Button to abort alert (5s window)"
    );

    // 5-second cancellation window
    while (millis() - startTime < 5000) {

      if (digitalRead(cancelButton) == LOW) {
        cancelPressed = true;
        break;
      }

      delay(100);
    }

    // If user cancels the alert
    if (cancelPressed) {

      BT.println("🚫 SOS Alert Cancelled by User.");
      Serial.println("🚫 SOS Alert Cancelled by User.");

      alarmState = 0;

    } else {

      // Send SOS alert
      BT.println("🚨 Sending SOS Alert via Bluetooth!");
      Serial.println("🚨 Sending SOS Alert via Bluetooth!");
    }

    // Turn off buzzer
    digitalWrite(buzzer, LOW);

    // Update LEDs
    digitalWrite(redLED, alarmState);
    digitalWrite(greenLED, !alarmState);

    delay(1000);

  } else {

    // Normal condition
    alarmState = 0;

    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenLED, HIGH);
  }

  // Display sensor information
  Serial.print("Pitch: ");
  Serial.print(pitch, 1);

  Serial.print(" | Roll: ");
  Serial.print(roll, 1);

  Serial.print(" | Vib: ");
  Serial.print(vib);

  Serial.print(" | Alarm: ");
  Serial.println(alarmState);

  delay(1000);
}
