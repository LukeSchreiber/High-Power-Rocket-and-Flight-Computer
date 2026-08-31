# Model Rocket Flight Computer & Airframe

A custom model rocket and embedded flight-computer project integrating ESP32-based data acquisition, environmental sensing, onboard data logging, flight analysis, and custom-designed mechanical components.

The project combines embedded C++ programming, electronics, sensor integration, CAD design, 3D printing, and experimental flight-data analysis into a complete rocket development platform.

---

## Project Overview

The goal of this project was to design and build a model rocket system capable of collecting and recording real flight data using a custom embedded flight computer.

The system uses an ESP32-based flight computer to interface with onboard sensors and record flight information for post-flight analysis. Custom mechanical components were designed for the rocket in SOLIDWORKS and exported as STL files for fabrication.

The project demonstrates the complete engineering process from design and programming through fabrication, testing, and data analysis.

---

## Repository Files

### Flight Computer Firmware

**[Flight_Computer_Program.ino](Flight_Computer_Program.ino)**

Arduino/ESP32 firmware used by the onboard flight computer for sensor interfacing, data acquisition, and flight-data logging.

---

### Flight Data

**[flight_log.xlsx](flight_log.xlsx)**

Recorded flight data used for post-flight analysis.

**[RocketData.png](RocketData.png)**

Visualization of the collected rocket flight data.

![Rocket Flight Data](RocketData.png)

---

## Mechanical Design

Custom rocket components were designed in SOLIDWORKS and exported as STL files for fabrication and 3D printing.

### Rocket Clamp

- **[RocketClamp.SLDPRT](RocketClamp.SLDPRT)** — Original SOLIDWORKS part
- **[RocketClamp.STL](RocketClamp.STL)** — 3D-printable version

### Rocket Fins

- **[RocketFins.SLDPRT](RocketFins.SLDPRT)** — Original SOLIDWORKS part
- **[RocketFins.STL](RocketFins.STL)** — 3D-printable version

### Nose Cone

- **[cone.SLDPRT](cone.SLDPRT)** — Original SOLIDWORKS part
- **[cone.STL](cone.STL)** — 3D-printable version

---

## OpenRocket Simulation

**[RocketProject.ork](RocketProject.ork)**

OpenRocket project file containing the rocket configuration used for design and flight simulation.

---

## Project Documentation

### Engineering Project Report

**[View Project PDF](rocket_project.pdf)**

Additional project documentation is available here:

**[View Additional Project PDF](rocket_project_2.pdf)**

---

## Project Images

The repository also contains a collection of project images:

**[Download Project Images](rocket-project-images.zip)**

These images document the rocket, flight computer, CAD designs, development process, and testing.

---

## Engineering Workflow

### 1. Rocket Design

The rocket geometry and major components were developed and evaluated before fabrication.

### 2. Mechanical CAD

Custom components including the rocket fins, nose cone, and mounting hardware were modeled in SOLIDWORKS.

### 3. Flight Computer Development

An embedded flight computer was programmed to interface with onboard sensors and record flight information.

### 4. Fabrication & Assembly

Mechanical components were exported to STL format for fabrication and integrated with the rocket and flight-computer hardware.

### 5. Flight Testing

The completed system was tested through an actual rocket flight while the onboard electronics collected flight data.

### 6. Data Analysis

Recorded flight data was exported and analyzed after recovery to evaluate the rocket's flight behavior and the performance of the flight-computer system.

---

## Repository Structure

```text
Model-Rocket-Project/
│
├── Flight_Computer_Program.ino
│
├── RocketClamp.SLDPRT
├── RocketClamp.STL
│
├── RocketFins.SLDPRT
├── RocketFins.STL
│
├── cone.SLDPRT
├── cone.STL
│
├── RocketProject.ork
│
├── flight_log.xlsx
├── RocketData.png
│
├── rocket-project-images.zip
│
├── rocket_project.pdf
├── rocket_project_2.pdf
│
└── README.md
```

---

## Key Skills Demonstrated

- Embedded systems development
- C++ / Arduino programming
- ESP32 development
- Sensor integration
- Data acquisition
- Flight-data logging
- Experimental testing
- Data analysis
- SOLIDWORKS CAD
- OpenRocket simulation
- 3D-printable component design
- Mechanical/electrical integration
- Model rocket design and fabrication

---

## Project Status

**Prototype Developed & Flight Tested**

The rocket and onboard flight-computer system were developed and tested, with flight data successfully recorded for post-flight analysis.

---

## Author

**Adriano Zagar**

Engineering Portfolio Project
