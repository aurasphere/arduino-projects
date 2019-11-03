# Arduino Sketches
This section contains some Arduino Sketches. Those are:
- **serial_led**: a program that turns on and off a led based on a character sent via serial port.
- **infrared_remote**: a program that emulates a TV remote by sending an infrared signal according to a serial input signal. This project has a dependency on [z3t0's Arduino IRremote](https://github.com/z3t0/Arduino-IRremote) repository.
- **serial_echo**: a program that sends any string received through serial port back via the same serial port. The purpose of this program is to test Bluetooth connections.
- **smart_carillon**: a program that handles a smart carillon. The program allows a device to connect via Bluetooth and send a melody to the carillon. The melody is stored into an EEPROM and can then be played at any time by pressing a button.