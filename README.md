# High-Power-Rocket-and-Flight-Computer
High-power rocket built with custom avionics, 3D-printed aerostructures, parachute recovery, key-locked ignition.
# Team-Developed Rocket and Flight Computer

A custom rocket and embedded flight-computer system developed by **Adriano Zagar and team**. The project combines avionics, sensor integration, aerodynamic simulation, mechanical design, fabrication, recovery, and system-level testing.

![Final assembled rocket](images/final-assembled-rocket.png)

## Project Overview

The goal of this project was to engineer and launch a complete rocket system with a custom ESP32-S3 flight computer. The rocket includes 3D-printed aerostructures, onboard altitude sensing and data logging, a parachute recovery system, and a key-locked ignition safety interlock.

## Key Features

- Custom ESP32-S3 flight computer
- BME280 barometric pressure sensor for altitude tracking
- Real-time flight-data logging to a microSD card
- TPS61023 boost converter for stable power delivery
- Aerodynamic modeling and stability validation in OpenRocket
- Custom fins, nose cone, and motor mount designed in SOLIDWORKS
- 3D-printed structural components
- Parachute recovery system with validated canopy geometry
- Custom ignition circuit with a key-locked safety interlock
- Bench testing and iterative field testing

## Tech Stack

| Area | Technologies and Components |
| --- | --- |
| Firmware | Embedded C++ |
| Microcontroller | ESP32-S3 |
| Sensor | BME280 barometric pressure sensor |
| Data Storage | microSD card |
| Power | TPS61023 boost converter |
| Mechanical Design | SOLIDWORKS |
| Flight Simulation | OpenRocket |
| Fabrication | 3D printing and hand-soldered perfboard |

## Development Process

1. **Design** – Modeled the custom aerostructures and mechanical components in SOLIDWORKS.
2. **Simulate** – Evaluated rocket stability and predicted flight performance using OpenRocket.
3. **Fabricate** – 3D printed and assembled the fins, nose cone, and motor mount.
4. **Build Avionics** – Soldered the flight computer and developed the ESP32-S3 firmware.
5. **Integrate** – Combined the electronics, sensors, structures, ignition controls, and recovery hardware.
6. **Test** – Conducted bench tests and field launches to evaluate the integrated system.

## Flight Computer

The flight computer is built around an ESP32-S3 and a hand-soldered perfboard assembly. A BME280 sensor records barometric pressure for altitude tracking, while flight data is written to a microSD card for analysis after recovery. A TPS61023 boost converter supports stable power delivery to the onboard electronics.

![ESP32-S3 flight computer](images/flight-computer.png)

## Mechanical and Aerodynamic Design

The fins, nose cone, and motor mount were designed in SOLIDWORKS and fabricated using 3D printing. OpenRocket simulations were used to check aerodynamic stability and support design decisions before field testing.

| Fin and Motor Mount | OpenRocket Simulation | Launch Setup |
| --- | --- | --- |
| ![3D-printed fin and motor mount](images/fin-motor-mount.png) | ![OpenRocket flight simulation](images/openrocket-simulation.png) | ![Rocket launch setup](images/launch-setup.png) |

## Engineering Challenges

### System Integration

The firmware, sensors, power system, recovery hardware, and mechanical structures had to operate as one flight-ready system. Bench testing was used to identify integration issues before field testing.

### Recovery System

The team designed a parachute recovery system and evaluated the canopy geometry to support a controlled descent and safe recovery of the rocket and onboard electronics.

### Ignition Safety

The project incorporated a custom ignition circuit and a key-locked interlock to reduce the risk of unintended activation. Testing was performed under team supervision and appropriate launch-site safety procedures.

| Safety Interlock | Recovery Parachute | Ignition System |
| --- | --- | --- |
| ![Key-locked safety interlock](images/safety-lock.png) | ![Recovery parachute](images/recovery-parachute.png) | ![Custom ignition system](images/custom-igniter.png) |

## Repository Structure

```text
.
├── firmware/       # ESP32-S3 source code
├── hardware/       # Schematics and wiring documentation
├── cad/            # SOLIDWORKS and printable part files
├── simulations/    # OpenRocket simulation files
├── data/            # Example flight logs and analysis
├── images/          # Project photos and diagrams
└── README.md
