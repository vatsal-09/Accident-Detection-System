# 🚨 Accident Detection System using Arduino and Bluetooth

An Arduino-based **Accident Detection and Alert System** that detects possible vehicle accidents using **vehicle tilt and vibration**. The system uses an **MPU6050 accelerometer/gyroscope sensor** and a **vibration sensor** to identify accident conditions and sends an **SOS alert via Bluetooth** to a paired mobile device.

---

## 📌 Project Overview

The Accident Detection System is designed to improve vehicle safety by automatically detecting abnormal vehicle tilt and vibration.

The system uses:

* **MPU6050** → Detects vehicle tilt using accelerometer data
* **Vibration Sensor** → Detects sudden vibration
* **Arduino Uno** → Main controller
* **HC-05 Bluetooth Module** → Sends accident/SOS alerts
* **Buzzer** → Provides an audible accident warning
* **Red LED** → Indicates accident/alarm state
* **Green LED** → Indicates normal state
* **Push Button** → Allows the user to cancel the SOS alert within 5 seconds

When an accident condition is detected, the system activates the buzzer and red LED and sends an alert through Bluetooth. The user gets a **5-second window** to cancel the SOS alert using the push button.

---

## ✨ Features

* 🚗 Accident detection using vehicle tilt
* 📳 Vibration-based accident detection
* 📐 MPU6050 accelerometer/gyroscope integration
* 📡 Bluetooth-based SOS alert
* 🔴 Red LED accident indication
* 🟢 Green LED normal-status indication
* 🔊 Buzzer alert
* 🛑 5-second SOS cancellation window
* 📱 Bluetooth communication with a paired mobile device
* 📟 Serial Monitor status information

---

## 🛠️ Technologies Used

* **Arduino Uno**
* **C/C++ (Arduino Programming)**
* **MPU6050**
* **HC-05 Bluetooth Module**
* **Vibration Sensor**
* **Buzzer**
* **LEDs**
* **Push Button**
* **Arduino Wire Library**
* **SoftwareSerial Library**

---

## 🔧 Components Required

| Component               | Purpose                                |
| ----------------------- | -------------------------------------- |
| Arduino Uno             | Main microcontroller                   |
| MPU6050                 | Measures acceleration and vehicle tilt |
| Vibration Sensor Module | Detects vibration                      |
| HC-05 Bluetooth Module  | Sends SOS alerts                       |
| Buzzer                  | Audible accident warning               |
| Red LED                 | Indicates accident/alarm               |
| Green LED               | Indicates normal condition             |
| Push Button             | Cancels SOS alert                      |
| Jumper Wires            | Circuit connections                    |
| Breadboard              | Circuit prototyping                    |
| 5V Power Supply         | Provides power                         |

The component list is based on the project report.

---

## 🔌 Pin Configuration

The following Arduino pins are used by the program:

| Component        | Arduino Pin |
| ---------------- | ----------: |
| Vibration Sensor |          D2 |
| HC-05 RX/TX      |    D10, D11 |
| Cancel Button    |          D6 |
| Buzzer           |          D7 |
| Red LED          |          D8 |
| Green LED        |          D9 |
| MPU6050          |         I²C |

### Bluetooth Configuration

```text
SoftwareSerial BT(10, 11);
```

The code uses:

```text
Arduino D10 → Bluetooth RX
Arduino D11 → Bluetooth TX
```

The Bluetooth module operates at **9600 baud** in the project code.

---

## ⚙️ How It Works

The system continuously monitors:

1. Vehicle tilt using the **MPU6050**
2. Vibration using the **vibration sensor**
3. User input using the **SOS cancel button**

The MPU6050 provides acceleration values:

```text
AcX
AcY
AcZ
```

These values are used to calculate:

```text
Pitch
Roll
```

The system then checks whether the calculated tilt exceeds the predefined threshold.

---

## 🧠 Accident Detection Logic

### Condition 1 — Significant Tilt

An accident is detected if:

```text
|Pitch| > 45°
OR
|Roll| > 45°
```

### Condition 2 — Vibration + Moderate Tilt

An accident is also detected when vibration occurs together with moderate vehicle tilt:

```text
Vibration detected
AND
(|Pitch| > 30° OR |Roll| > 30°)
```

Therefore:

```text
                ┌─────────────────┐
                │   MPU6050       │
                │ Tilt Detection  │
                └────────┬────────┘
                         │
                         ▼
                  Calculate Pitch
                    and Roll
                         │
                         ▼
              ┌─────────────────────┐
              │ Accident Condition? │
              └──────────┬──────────┘
                         │
             ┌───────────┴───────────┐
             │                       │
            YES                      NO
             │                       │
             ▼                       ▼
       🔴 Red LED ON           🟢 Green LED ON
       🔊 Buzzer ON             Buzzer OFF
       📡 Bluetooth Alert
             │
             ▼
       5 Second Cancel Window
             │
       ┌─────┴─────┐
       │            │
    Cancel       No Cancel
       │            │
       ▼            ▼
   Stop Alert    SOS Alert
```

The detection conditions and thresholds are implemented in the provided Arduino program.

---

## 🛑 SOS Cancellation

After an accident is detected, the system gives the user **5 seconds** to cancel the alert.

The Bluetooth and Serial Monitor display:

```text
Press SOS Cancel Button to abort alert (5s window)
```

If the button is pressed:

```text
🚫 SOS Alert Cancelled by User.
```

Otherwise:

```text
🚨 Sending SOS Alert via Bluetooth!
```

This provides a short opportunity to prevent a false alarm.

---

## 📡 Bluetooth Communication

The project uses an **HC-05 Bluetooth module** to communicate with a paired mobile device.

The system can send messages such as:

```text
Accident Detector Ready
```

```text
⚠️ Accident Detected!
```

```text
🚫 SOS Alert Cancelled by User.
```

```text
🚨 Sending SOS Alert via Bluetooth!
```

---

## 📂 Project Structure

```text
Accident-Detection-System/
│
├── accident_detection.ino
├── README.md
└── images/
    ├── circuit.png
    └── project-demo.png
```

---

## 🚀 Getting Started

### 1. Install Arduino IDE

Install the **Arduino IDE** and configure it for the Arduino Uno.

### 2. Connect the Components

Connect the MPU6050, vibration sensor, HC-05 Bluetooth module, LEDs, buzzer, and cancel button according to the project's circuit configuration.

### 3. Open the Arduino Code

Open:

```text
accident_detection.ino
```

### 4. Select Arduino Uno

In Arduino IDE:

```text
Tools → Board → Arduino Uno
```

### 5. Select the Correct COM Port

```text
Tools → Port → COMx
```

### 6. Upload the Program

Click:

```text
Upload
```

### 7. Open Serial Monitor

Set the baud rate to:

```text
9600
```

---

## 💻 Example Serial Output

When the system starts:

```text
Tilt-based Accident Detector Initialized...
```

The Bluetooth module also receives:

```text
Accident Detector Ready
```

During normal operation, the Serial Monitor displays:

```text
Pitch: 4.2 | Roll: 2.7 | Vib: 0 | Alarm: 0
```

When an accident condition is detected:

```text
⚠️ Accident Detected!

Press SOS Cancel Button to abort alert (5s window)
```

If the user cancels:

```text
🚫 SOS Alert Cancelled by User.
```

If the user does not cancel:

```text
🚨 Sending SOS Alert via Bluetooth!
```

---

## 📊 System Status

| Condition         | Green LED | Red LED | Buzzer          | Bluetooth            |
| ----------------- | --------- | ------- | --------------- | -------------------- |
| Normal            | 🟢 ON     | OFF     | OFF             | Normal status        |
| Accident Detected | OFF       | 🔴 ON   | 🔊 ON           | Accident alert       |
| SOS Cancelled     | 🟢 ON     | OFF     | OFF             | Cancellation message |
| SOS Sent          | OFF       | 🔴 ON   | OFF after alert | 🚨 SOS message       |

The report states that significant tilt or vibration activates the red LED and buzzer, sends an alert through Bluetooth, and allows cancellation within 5 seconds.

---

## 🎯 Applications

This system can be used as a prototype for:

* 🚗 Vehicle safety systems
* 🏍️ Two-wheeler accident detection
* 🚑 Emergency alert systems
* 🚘 Automotive safety projects
* 🎓 Academic embedded-systems projects
* 🛡️ Basic accident monitoring systems

---

## 🔮 Future Scope

The project can be enhanced by integrating:

### 📍 GPS Module

A GPS module can be used to obtain the vehicle's real-time location.

### 📱 GSM Module

A GSM module can automatically send accident alerts and location information to emergency contacts.

### 🌐 IoT Integration

The system could send accident information to a cloud platform for remote monitoring.

### 📊 Mobile Application

A dedicated mobile application could display:

* Accident status
* Vehicle location
* Emergency alerts
* Sensor information

The project report specifically proposes **GSM and GPS integration** to automatically send location and alert messages to emergency contacts.

---

## 📸 Project Demonstration

Add photographs of your implemented circuit here:

```markdown
![Accident Detection System](images/circuit.png)
```

You can also add your demonstration video link:

```markdown
[🎥 Watch Project Demonstration](YOUR_GOOGLE_DRIVE_LINK)
```

---

## 📈 Results

The implemented system successfully demonstrates basic accident detection and alert functionality.

When significant vehicle tilt or vibration is detected:

```text
MPU6050 / Vibration Sensor
          ↓
Accident Detection
          ↓
Red LED + Buzzer
          ↓
Bluetooth Alert
          ↓
5-Second Cancellation Window
          ↓
SOS Alert
```

The system can detect an accident condition, activate the warning indicators, communicate the alert through Bluetooth, and allow the user to cancel the alert within the specified 5-second window.

---

## ✅ Conclusion

The **Accident Detection System using Arduino and Bluetooth** successfully demonstrates a basic vehicle safety mechanism that detects possible accidents based on tilt and vibration.

The combination of **MPU6050, vibration sensor, Arduino Uno, HC-05 Bluetooth, buzzer, LEDs, and cancel button** provides a simple prototype for accident detection and alert generation.

The system can be further improved by integrating **GPS and GSM modules** for automatic location tracking and emergency communication.

---

## 👨‍💻 Project Information

**Project:** Accident Detection System using Arduino and Bluetooth
**Project Type:** ECC 512 Project
**Platform:** Arduino Uno
**Programming Language:** Arduino C/C++
**Communication:** Bluetooth
**Primary Sensors:** MPU6050 + Vibration Sensor

### Registration Numbers

```text
1176
1177
1194
1195
```

---

## 🤝 Contributing

Contributions and improvements are welcome!

1. Fork this repository
2. Create a new branch
3. Make your changes
4. Commit your changes
5. Push the branch
6. Create a Pull Request

---

## 📄 License

This project is intended for **educational and academic purposes**.
