# PathFinder-Bot 🤖🏎️

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Hardware](https://img.shields.io/badge/Hardware-Arduino_Uno-teal)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

**PathFinder-Bot** is an autonomous, high-speed line-tracking robot. It leverages a 6-sensor IR array in tandem with **PID (Proportional, Integral, Derivative) Control logic** to ensure smooth and accurate line tracking over complex paths. 

<div align="center">
  <img src="assets/bot_photo.jpeg" alt="PathFinder Bot Photo" width="400"/>
  <br/>
  <em>The PathFinder Robot</em>
</div>

---

## 🎥 Bot in Action
Watch the bot seamlessly navigate the track!


<div align="center">
  <video src="assets/bot_demo.mp4" width="600" controls>
    <a href="assets/bot_demo.mp4">Download/Play Video</a>
  </video>
</div>

---

## 🛠️ Tech Stack & Components
To build this robot, the following components were utilized:
- **Microcontroller:** Arduino Uno
- **Sensor Array:** 8-Channel IR Sensor Array (6 sensors utilized for precise PID logic)
- **Motor Driver:** L298N Dual H-Bridge Motor Driver
- **Actuators:** 2x DC Gear Motors
- **Power Supply:** Li-ion Battery configuration
- **Chassis:** Custom Robot Chassis with Caster Wheel
- **Language:** C/C++ (Arduino IDE)

---

## 🧠 Features & Capabilities
1. **PID Control System:** Calculates proportional, integral, and derivative errors continuously for smooth turning, eliminating "wobbly" movements.
2. **Junction Detection:** Capable of recognizing and responding to grid line intersections or sharp angles.
3. **Responsive Autonomy:** High polling rate on the IR sensors allows the robot to handle high-speed straight lines and tight curves.

---

## 🔌 Circuit & Wiring (Pin Configuration)

### 🤖 Robot Chassis Layout
The robot uses a **differential drive 3-wheel configuration**:
- **Front:** 1x Free-turning 360° Caster Wheel (Maintains balance and allows sharp turns).
- **Rear:** 2x Drive Wheels (Left & Right), each connected individually to a DC Gear Motor.

### 🔗 Connection Diagram

```mermaid
graph TD
    classDef hardware fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000;
    classDef power fill:#ebb4b4,stroke:#333,stroke-width:2px,color:#000;
    
    Battery["Battery Pack (7.4V / 12V)"]:::power -->|"VCC"| Switch("Power Switch")
    Switch -->|"Raw Power"| L298N["L298N Motor Driver"]:::hardware
    L298N -->|"5V Out"| Uno["Arduino Uno (5V/VIN)"]:::hardware
    
    Battery -->|"GND"| GND(("Common GND"))
    L298N ---|"GND"| GND
    Uno ---|"GND"| GND

    subgraph "Front Sensor Array"
        S1["IR 1 (Ex-Left)"]
        S2["IR 2 (Left)"]
        S3["IR 3 (Mid-Left)"]
        S4["IR 4 (Mid-Right)"]
        S5["IR 5 (Right)"]
        S6["IR 6 (Ex-Right)"]
    end

    S1 -->|"D13"| Uno
    S2 -->|"D12"| Uno
    S3 -->|"D11"| Uno
    S4 -->|"D4"| Uno
    S5 -->|"D3"| Uno
    S6 -->|"D2"| Uno

    subgraph "Rear Drive Motors (2 Wheels)"
        motorL["Left DC Motor"]:::hardware
        motorR["Right DC Motor"]:::hardware
    end

    L298N -->|"OUT3, OUT4"| motorL
    L298N -->|"OUT1, OUT2"| motorR

    Uno -->|"D5 (PWM)"| L298N
    Uno -->|"D8 (IN1)"| L298N
    Uno -->|"D9 (IN2)"| L298N
    Uno -->|"D10 (PWM)"| L298N
    Uno -->|"D7 (IN3)"| L298N
    Uno -->|"D6 (IN4)"| L298N
```


### Motor Driver (L298N)
| Arduino Pin | Motor Driver Pin | Purpose |
| ----------- | ---------------- | ------- |
| `D5` (PWM)  | ENA              | Right Motor Speed |
| `D8`        | IN1              | Right Motor Direction |
| `D9`        | IN2              | Right Motor Direction |
| `D10` (PWM) | ENB              | Left Motor Speed |
| `D7`        | IN3              | Left Motor Direction |
| `D6`        | IN4              | Left Motor Direction |

### IR Sensor Array
| Arduino Pin | Sensor Position |
| ----------- | --------------- |
| `D13`       | Ex-Left (1)     |
| `D12`       | Left (2)        |
| `D11`       | Mid-Left (3)    |
| `D4`        | Mid-Right (4)   |
| `D3`        | Right (5)       |
| `D2`        | Ex-Right (6)    |

---

## 🚀 How to Run

1. **Clone the repository:**
   ```bash
   git clone https://github.com/fenilfinava/PathFinder-Bot.git
   cd PathFinder-Bot
   ```
2. **Setup Hardware:** Assemble the components according to the wiring table above.
3. **Open the code:** Open `src/line_follower.ino` using the Arduino IDE. 
4. **Tune PID Values:** The default `Kp`, `Ki`, and `Kd` values may need to be adjusted based on your robot's weight, battery voltage, and track properties. Change them at the top of the file:
   ```cpp
   float Kp = 4.0;
   float Ki = 0.001;
   float Kd = 2.0;
   ```
5. **Upload & Test:** Select your Arduino Uno board and COM port, then hit Upload. Place the robot on a test track and watch it go!

---

## 👨‍💻 Author
**Fenil Finava**
*Computer Engineering Student | Tech Enthusiast*
