# Underground Cable Fault Detection System — Arduino

Arduino-oriented reference implementation for monitoring a cable-fault input and reporting the detected fault location/status over Serial.

## Important
The original resume does not specify the exact sensor/module and electrical fault-location circuit. The firmware therefore uses an **analog measurement interface as an explicit implementation assumption**. Hardware calibration must be performed against the actual circuit before deployment.

## Features
- Analog measurement
- Threshold-based fault classification
- Serial monitoring
- Simple fault-location estimation
- Configurable thresholds

## Hardware Assumption
- Arduino-compatible board
- Analog measurement input
- Fault-sensing circuit producing a calibrated analog voltage

## Run
Open `src/cable_fault_detection.ino` in Arduino IDE, select the target board, verify pin configuration, and upload.

## Validation
Software logic should be tested with representative ADC values before connecting a physical sensing circuit. No physical hardware result is claimed by this repository.
