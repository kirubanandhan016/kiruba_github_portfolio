# ESP32-CAM Object Detection

An ESP32-CAM reference project for camera initialization, frame capture, and an object-detection integration point.

## Implementation note
The resume identifies ESP32-CAM object detection but does not specify the exact model/runtime. This repository therefore provides a clean camera-capture foundation with a clearly isolated detection interface rather than claiming a particular model or accuracy.

## Features
- ESP32-CAM camera initialization
- JPEG frame capture
- Serial status reporting
- Detection hook for an application-specific model
- Basic frame error handling

## Hardware
- AI Thinker ESP32-CAM or compatible ESP32-CAM board
- USB-to-TTL programmer for flashing where required

## Setup
1. Install ESP32 board support in Arduino IDE.
2. Select the correct ESP32-CAM board.
3. Update camera pin configuration if your board differs.
4. Upload using the board's documented programming procedure.

## Validation
The source is intended for Arduino/ESP32 compilation. Actual camera operation requires the physical board and camera module. No detection accuracy or hardware test result is claimed here.

## Future Improvements
- Integrate a measured Edge Impulse/TFLite Micro model
- Add confidence reporting
- Add web/serial result interface
- Measure frame rate and memory usage
