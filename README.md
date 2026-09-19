# Multi-User Human Reaction Time Measurement Device

![Status](https://img.shields.io/badge/Status-Completed-success)
![Platform](https://img.shields.io/badge/Hardware-Arduino%20UNO%20R3-blue)
![Circuitry](https://img.shields.io/badge/Power%20Electronics-IRF540N%20MOSFET-red)
![Fabrication](https://img.shields.io/badge/Fabrication-FDM%203D%20Printing-orange)
![Interface](https://img.shields.io/badge/DAQ-USART%20%7C%20Excel%20Data%20Streamer-green)

A modular, cost-effective mechatronic instrument designed for accurate mental chronometry and psychomotor reaction testing across multiple subjects simultaneously. The system integrates low-latency embedded firmware, dedicated power switching stages for high-intensity visual and acoustic stimuli, and custom ergonomic enclosures.

---

## 📌 Project Highlights
* **Multi-Subject Testing:** Measures up to 8 participants simultaneously with millisecond-level acquisition accuracy, enabling simple, go/no-go, and choice reaction time paradigms.
* **Dual Stimulus Delivery:** High-output visual stimuli (3W power LEDs across four optical wavelengths: 460 nm, 525 nm, 590 nm, 625 nm) and an acoustic buzzer (2048 Hz resonance).
* **Power Electronics Design:** Utilizes IRF540N power MOSFETs with calculated gate current-limiting resistors and pull-down protection to safely switch loads directly from external/USB power rails.
* **In-Situ Parameter Control:** Integrated bi-directional serial interface allowing real-time tuning of fixed/random inter-stimulus intervals (ISI), stimulus modes, and frequencies without test interruption.
* **Field-Tested:** Validated and benchmarked in a secondary school laboratory environment with statistical distribution logging.

---

## 🛠 Hardware Architecture & Schematics

| Component | Specification / Role | Detail |
|---|---|---|
| **MCU** | Arduino UNO R3 | Core timing and USART communication (16 MHz crystal, 0.01% stability) |
| **Power Stages** | 5x IRF540N N-Channel MOSFETs | Fast low-side switching for 3W LEDs and passive buzzer |
| **Visual Stimuli** | 4x High-Power 3W LEDs | Blue (460 nm), Green (525 nm), Yellow (590 nm), Red (625 nm) |
| **Acoustic Stimulus** | 5V Passive Magnetic Buzzer | Frequency adjustable via MCU PWM; 85 dB SPL @ 10 cm |
| **Input Buttons** | 8x Sanwa OBSF-30 Arcade Switches | Low-travel, momentary snap-in switches mapped to dedicated digital/analog pins |
| **Enclosures** | Custom FDM 3D Printed Parts | Protective module cases, button pods, and magnetic stimulus bracket |

### Electrical Design Consideration
To protect the MCU GPIO pins from excessive current spikes caused by gate input capacitance, series gate resistors ($R_G = 270\,\Omega$) were calculated using Ohm's law:

$$R_G \ge \frac{U_{pin}}{I_{max}} = \frac{5\,\text{V}}{0.02\,\text{A}} = 250\,\Omega$$

Static discharge and unintended gate floating are suppressed via $10\,\text{k}\Omega$ pull-down resistors between gate and drain/ground.

---

## 💻 Firmware & Data Acquisition Pipeline

```text
[ Stimulus Trigger ] ──> [ Timer Start (millis) ] ──> [ Pin Change Polling (8 Channels) ]
                                                                   │
[ USART Data Stream (9600 Baud) ] <── [ Fixed/Dynamic Delay ] <────┘
            │
            ▼
[ Real-Time Data Acquisition & Statistical Analysis in Excel ]
