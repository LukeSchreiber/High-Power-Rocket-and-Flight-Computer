# Model Rocket & ESP32 Flight Computer

A model rocket built from scratch around a custom ESP32-S3 flight computer that logs
barometric altitude, pressure, and temperature to onboard flash at 20 Hz.

The project covers the full build: airframe design in OpenRocket, custom fins, nose cone,
and launch-rail hardware modeled in SOLIDWORKS and 3D printed, firmware written in
Arduino/C++, a homemade igniter and safety-interlock launch controller, and flight testing.

<img src="media/launch.gif" width="320" alt="Rocket launching from the field">

---

## Flight Computer

<img src="media/flight-computer.png" width="520" alt="ESP32-S3 flight computer on perfboard">

| Part | Role |
| --- | --- |
| ESP32-S3 WROOM (Freenove) | Main controller, onboard LittleFS flash storage |
| BME280 (I²C, `0x76`) | Barometric pressure, temperature, derived altitude |
| TPS61023 boost converter | Steps battery voltage up to the board's power rail |
| Perfboard + soldered harness | Flight-ready wiring, no breadboard jumpers |

Wiring is I²C on `SDA = GPIO21`, `SCL = GPIO22`.

### Firmware

[`firmware/Flight_Computer_Program/Flight_Computer_Program.ino`](firmware/Flight_Computer_Program/Flight_Computer_Program.ino)

On boot the firmware averages 10 pressure samples to establish a ground baseline, opens the
next unused `flight_N.csv` on LittleFS, and logs continuously:

- **20 Hz sampling** (50 ms interval), pressure oversampled ×16 for resolution
- **Altitude** derived from the barometric formula against the ground baseline
- **Flushed to flash every second**, so an unexpected power loss costs at most 1 s of data
- **Auto-incrementing flight files** — a new log per power cycle, nothing overwritten

Logged columns: `time_ms, pressure_hPa, temperature_C, altitude_m`

### Serial commands

Connect at **115200 baud** and send a single character:

| Key | Action |
| --- | --- |
| `L` | List stored flight logs and flash usage |
| `D` | Dump all logs over serial for retrieval |
| `W` | Erase all logs |
| `S` | Pause / resume logging |

### Building

Requires the ESP32 board support package plus the `Adafruit_BME280` and `Adafruit_Sensor`
libraries. Open the sketch folder in the Arduino IDE, select an ESP32-S3 board, and upload.

---

## Mechanical Design

Custom components were modeled in SOLIDWORKS and 3D printed. Sources are in
[`cad/solidworks/`](cad/solidworks/), print-ready meshes in [`cad/stl/`](cad/stl/).

| Component | SOLIDWORKS | STL |
| --- | --- | --- |
| Fin can | [RocketFins.SLDPRT](cad/solidworks/RocketFins.SLDPRT) | [RocketFins.STL](cad/stl/RocketFins.STL) |
| Nose cone | [NoseCone.SLDPRT](cad/solidworks/NoseCone.SLDPRT) | [NoseCone.STL](cad/stl/NoseCone.STL) |
| Launch-rail clamp | [RocketClamp.SLDPRT](cad/solidworks/RocketClamp.SLDPRT) | [RocketClamp.STL](cad/stl/RocketClamp.STL) |

<img src="media/fin-motor-mount.png" width="300" alt="Printed fin can and motor mount">

The finished airframe — 3D-printed fin can, nose cone, and painted body tube:

<table>
  <tr>
    <td align="center">
      <img src="media/final-assembled-rocket.png" width="240" alt="Adriano holding the completed rocket"><br>
      <sub>Adriano with the completed rocket</sub>
    </td>
    <td align="center">
      <img src="media/luke-with-rocket.jpg" width="240" alt="Luke holding the rocket beside the launch rod"><br>
      <sub>Luke at the pad before launch</sub>
    </td>
  </tr>
</table>

Recovery is a parachute deployed by the motor's ejection charge.

<img src="media/recovery-parachute.png" width="300" alt="Recovery parachute">


---

## Simulation

[`simulation/RocketProject.ork`](simulation/RocketProject.ork) — OpenRocket model used to size
the airframe and predict the flight profile.

![OpenRocket vertical motion vs. time](simulation/openrocket-vertical-motion.png)

| Predicted | Value |
| --- | --- |
| Apogee | 390 ft |
| Time to apogee | 3.2 s |
| Total flight time | 19.3 s |
| Peak velocity | 327 ft/s |
| Peak acceleration | 317 ft/s² |

---

## Flight Data

[`data/flight_log.xlsx`](data/flight_log.xlsx) — a 200-row flight profile with per-phase
labels (ignition, powered ascent, coast, apogee, descent, landed), matching the CSV schema
the flight computer writes.

> **Note:** this workbook is **synthetic data generated from the OpenRocket simulation above**,
> not telemetry recovered from a launch — it is labeled as such in the file itself
> (`Data_Source = SYNTHETIC_SIMULATION`). It exists to demonstrate the logging format and
> analysis pipeline. Recorded flight logs are not currently in this repository.

---

## Launch System

<img src="media/custom-igniter.png" width="300" alt="Hand-built nichrome igniter">
<img src="media/safety-lock.png" width="300" alt="Launch controller with safety interlock">

A hand-built nichrome igniter fired from a 9 V controller with a **two-stage safety
interlock** — an arming switch in series with a momentary launch button, so the igniter
cannot be energized by a single accidental press.

<img src="media/launch-setup.png" width="360" alt="Rocket on the pad before launch">

---

## Documentation

- [Project report](docs/rocket-flight-computer-report.pdf) — written write-up of the design and build
- [Photo report](docs/rocket-flight-computer-photo-report.pdf) — illustrated build documentation

---

## Repository Structure

```text
.
├── firmware/
│   └── Flight_Computer_Program/     Arduino sketch (ESP32-S3 + BME280 logger)
├── cad/
│   ├── solidworks/                  Editable SOLIDWORKS parts
│   └── stl/                         Print-ready meshes
├── simulation/                      OpenRocket model + predicted flight profile
├── data/                            Flight-log workbook (synthetic — see above)
├── docs/                            Project reports (PDF)
└── media/                           Launch footage and build photos
```

---

## Skills

Embedded C++ · ESP32 · I²C sensor integration · onboard data logging · SOLIDWORKS ·
3D printing · OpenRocket simulation · circuit prototyping and soldering · flight testing

---

## Status

Airframe, avionics, and launch system built and flown. Next step is recovering a real
logged flight and replacing the synthetic dataset with measured telemetry.

---

## Authors

Built as a two-person team project by **Adriano Zagar** and **Luke Schreiber**.
