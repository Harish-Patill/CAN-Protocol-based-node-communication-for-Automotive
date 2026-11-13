# can_node_communication_automotive

CAN bus communication between three PIC18F4580 ECU nodes, simulating an automotive dashboard network.

A car dashboard built from three ECUs (Electronic Control Units) that talk over a CAN bus, similar to how real vehicles connect their internal systems. Each ECU handles one job, and together they show speed, gear, RPM and indicator status on a dashboard display.

## Nodes

| Node | Role |
|---|---|
| ECU1 | Reads speed (ADC) and gear position (matrix keypad), transmits over CAN |
| ECU2 | Reads RPM (ADC) and processes indicator status (digital keypad) |
| ECU3 | Receives all CAN messages, displays data on LCD, controls indicator LEDs |

## Hardware

- **Microcontroller:** PIC18F4580 (with built-in CAN module)
- **Display:** 16x2 character LCD
- **Inputs:** Matrix / digital keypad, ADC
- **Tools:** MPLAB X v6.25, XC8 v3.10

## CAN Messages

| ID | Parameter | Sent From |
|---|---|---|
| 0x10 | Speed | ECU1 |
| 0x20 | Gear | ECU1 |
| 0x30 | RPM | ECU2 |
| 0x40 | Engine Temp | ECU2 |
| 0x50 | Indicator | ECU2 |

## Features

- Multi-ECU communication over the CAN bus
- Real-time display of speed, gear, RPM and indicator status
- Collision alert when the gear is set to the collision gear
- Indicator control with blinking arrows
- Modular code, with each ECU in its own project

## Build

Open each `.X` folder in MPLAB X and build it separately, then flash each board.

- `ECU1.X`: sensor node (speed and gear)
- `ECU2.X`: sensor node (RPM and indicators)
- `ECU3.X`: dashboard node (display)



<!-- # CAN Dashboard Network

A small car dashboard built with three PIC18F4580 boards that share one CAN bus. Each board does one job: two of them read the car's inputs and send them out, and the third collects everything and shows it on a screen.

## How the boards work

- **Board 1** reads the speed knob and the gear buttons.
- **Board 2** reads the RPM and the turn-signal buttons.
- **Board 3** listens to the bus, shows the readings on an LCD, and drives the indicator lights.

## Parts

- PIC18F4580 microcontroller on each board
- 16x2 LCD and 7-segment display
- Keypad and analog inputs
- Built with MPLAB X and the XC8 compiler

## Message IDs

Each value sent on the bus has its own ID, so the receiving board knows what it's getting:

- `0x10` speed
- `0x20` gear
- `0x30` RPM
- `0x40` engine temperature
- `0x50` indicator

## Building

Each board has its own project folder. Open a folder in MPLAB X, build it, and flash it to that board. The three folders are `ECU1.X`, `ECU2.X` and `ECU3.X`. -->