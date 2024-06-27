# Do it yourself Arduino EMF reader
Pdf explenation with images [here](https://github.com/Hrodebert17/Do-it-yourself-Arduino-EMF/blob/main/Do%20it%20yourself%20Arduino%20EMF%20reader.pdf).
## Required components
- Any Arduino (I personally would recommend an Arduino Nano Every)
- A Bluetooth HC-05 module
- A green LED
- A yellow LED
- A red LED
- 3 x 220-ohm resistors
- 3 x 1k ohm resistors
- Power supply module
- Battery
- Battery to DC 9V converter
- 12 male jumpers
- Breadboard
- KY-025

## How to build

1. Connect the power supply to the breadboard
2. Connect the Bluetooth module:
   - The Vcc pin has to go into the Arduino/Power Supply 5v
   - The GND pin has to go into the Arduino/Power Supply ground
   - Connect TXD to digital pin 2
   - Connect RXD:
     - Connect one resistor of 1k ohm to a jumper going to Arduino digital pin 3
     - Connect two resistors together of 1k ohm to the Arduino/Power Supply ground
3. Connect the KY-025:
   - The + pin to the 5v Arduino/Power Supply
   - The G pin to the Arduino/Power Supply ground
   - The A0 pin to your Arduino A7 pin
4. Connect the LEDs:
   - Connect all the LEDs ground (small leg) to Arduino/Power Supply ground using a 220-ohm resistor
   - **Green LED:** Connect the long leg to Arduino pin number 20
   - **Yellow LED:** Connect the long leg to Arduino pin number 19
   - **Red LED:** Connect the long leg to Arduino pin number 18
5. Connect the battery to the power supply WITHOUT TURNING THE POWER SUPPLY ON
6. Connect the Power Supply 5v to Arduino Vin
7. Connect the Power Supply ground to Arduino gnd

## How the circuit should look like

[Include a diagram here if available]

## Customize Bluetooth settings

1. Upload this script
2. Disconnect your Arduino
3. Hold the button on the front side of HC-05 while giving power to Arduino until the main power LED of the module does not emit light
4. Upload it to your Arduino and open a serial monitor at the baud rate of 38400
5. Customize your Bluetooth settings using this table. Remember to use the command `AT+PSWD` to get your module password and `AT+NAME` to get your module name.
6. Remove the power from the sensor by shutting down Arduino
7. Upload this sketch to Arduino

## How to connect to Bluetooth

1. Once you set up all your settings following steps 3-5, make sure to power the circuit via battery or via cable.
2. Then, using the name and password you discovered earlier, connect to your Bluetooth device and install this app.
3. From there, you can press the Menu button on the top left of your screen, go into devices -> Bluetooth Classic, and select your device (the HC-05 module).
4. This will connect you to the Bluetooth of the Arduino, where you can perform the following commands:

### Commands and Functions

- **Ping:** Sends a simple message to the Arduino, typically used to check the connection status.
  - **Command:** Ping
  - **Function:** Verifies that the Bluetooth connection to the Arduino is active by sending a straightforward message.

- **SetPin:** Allows you to set the value of a specific Arduino pin, enabling control over the pin's state.
  - **Command:** SetPin
  - **Function:** Sets the digital or analog value of an Arduino pin as specified.

- **PauseAll:** Stops the entire program execution on the Arduino.
  - **Command:** PauseAll
  - **Function:** Halts all operations running on the Arduino until a resume command is received.

- **PauseNormal:** Stops the entire program execution except for the Bluetooth command processing.
  - **Command:** PauseNormal
  - **Function:** Pauses all operations except for those related to Bluetooth communication, allowing remote control and management to continue.

- **GetEMF:** Returns the Electromotive Force (EMF) reading from the Arduino, where 1024 indicates low EMF and 0 indicates high EMF.
  - **Command:** GetEMF
  - **Function:** Provides the current EMF reading from the Arduino's sensors.

- **autoSendEMF:** Toggles automatic sending of EMF data approximately every 100 milliseconds. This command can be paused.
  - **Command:** autoSendEMF
  - **Function:** Automatically transmits EMF readings at regular intervals, which can be paused with relevant commands.

