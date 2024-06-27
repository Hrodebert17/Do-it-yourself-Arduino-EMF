#include <SoftwareSerial.h>

// Pin out for hc-05/hc-06
#define rxPin 2
#define txPin 3
// This has to match the baudRate you set up for your Bluetooth module
#define baudRate 57600
// The analog pin for the magnetic spring
#define ANALOG_MAGNETIC_FIELD A7
// The Arduino pins for your LEDs
#define GREEN_PIN 20
#define YELLOW_PIN 19
#define RED_PIN 18
// Define all the global variables here
int mag_a; // Magnetic field analog output
String data; // The Bluetooth input
SoftwareSerial bluetooth(rxPin, txPin); // The Bluetooth module
// Bluetooth settings
bool pause = false; // If this variable is set to true, then the Arduino code will pause except for the Bluetooth
bool autoSendEMF = false; // If this variable is true, then the Arduino will send the EMF about every 100 ms to the Bluetooth module

void setup() {
  // Start the Bluetooth communication and the Serial Communication
  Serial.begin(9600);
  bluetooth.begin(baudRate);
  // Set up the pins
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  // Flash the user with all the LEDs to indicate that the device is ready
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(YELLOW_PIN, HIGH);
  digitalWrite(RED_PIN, HIGH);
  delay(2000);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);

  // Print the menu to Bluetooth
  bluetooth.println("**************************************************************************************");
  bluetooth.println("*                            EMF Bluetooth DIY Menu                                  *");
  bluetooth.println("*Ping (Sends a simple message to Arduino)                                            *");
  bluetooth.println("*SetPin (Allows you to set the value of an Arduino pin)                               *");
  bluetooth.println("*PauseAll (Stops the whole program execution)                                        *");
  bluetooth.println("*PauseNormal (Stops the whole program except the Bluetooth commands)                 *");
  bluetooth.println("*GetEMF (Returns the EMF read by Arduino, 1024 is low EMF, 0 is high EMF)            *");
  bluetooth.println("*autoSendEMF (Switch command, if on it sends EMF data about every 100 ms) (pausable) *");
  bluetooth.println("**************************************************************************************");
}

void loop() {
  // If the program is not paused, then it will get the EMF data and light the LED depending on the level
  /*
  - Greater than 682 is a low EMF meaning that the green LED will be turned on
  - Less than 682 but greater than 341 is a medium EMF meaning that the yellow LED will be on
  - Less than 341 is a high EMF so the red LED will be on
  */
  if (!pause) {
    mag_a = analogRead(ANALOG_MAGNETIC_FIELD);  

    Serial.print("Magnetic field: ");
    Serial.print(mag_a);
    Serial.print(" ");

    if (mag_a > 682) {
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(RED_PIN, LOW);
      Serial.println("Low");
    } else if (mag_a > 341) {
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      Serial.println("Medium");
    } else {
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      Serial.println("High");
    }

    if (autoSendEMF) {
      bluetooth.print("EMF: ");
      bluetooth.println(mag_a);
    }
  }
  // Uses a function to analyze Bluetooth input (if available)
  readBluetoothSerial();

  // Sends the user back a message to let them know the Bluetooth is working
  if (data == "Ping") {
    Serial.println(data);
    bluetooth.println("Data received.");
  }
  // Allow the user to turn on / turn off any Arduino pin
  if (data.startsWith("SetPin")) {
    bluetooth.println("Please insert the desired pin.");
    while (!bluetooth.available()) {}
    readBluetoothSerial();
    int pin = data.toInt();
    bluetooth.println("Insert the value: ");
    while (!bluetooth.available()) {}
    readBluetoothSerial();
    digitalWrite(pin, data.toInt());
  }
  // Pauses the entire program
  if (data == "PauseAll") {
    bluetooth.println("Program paused. Send 'Resume' to resume");
    while(true) {
      while (!bluetooth.available()) {}
      readBluetoothSerial();
      if (data == "Resume") {
        break;
      }
    }
  }
  // Pauses the program except the Bluetooth functions
  if (data == "PauseNormal") {
    pause = true;
    bluetooth.println("Program paused (except Bluetooth). Send 'ResumeNormal' to resume");
  }
  // Resumes the program from "PauseNormal"
  if (data == "ResumeNormal") {
    pause = false;
    bluetooth.println("Program resumed");
  }
  // Sends the EMF data via Bluetooth
  if (data == "GetEMF") {
    bluetooth.print("EMF: ");
    bluetooth.println(mag_a);
  }
  // Sends the EMF data about every 100 ms to the user via Bluetooth
  if (data == "autoSendEMF") {
    if (autoSendEMF) {
      bluetooth.println("autoSendEMF is now off");
      autoSendEMF = false;
    } else {
      bluetooth.println("autoSendEMF is now on");
      autoSendEMF = true;
    }
  }
  // Pause the program for 1/10 of a second
  delay(100);
}

// Function to read the Bluetooth input
void readBluetoothSerial() {
  // Initialize the data variable as empty
  data = "";
  // Read the Bluetooth input
  while (bluetooth.available()) {
    data += char(bluetooth.read());
  }
  // After Arduino retrieves all the input, clean it by removing the last two chars which are special chars (like '/n')
  if (data.length() > 2) { 
    String tempData;
    for(int i = 0; i < data.length() - 2; i++) {
      tempData += data[i];
    }
    // Save the changes to the data variable
    data = tempData;
  }
}
