//This is a program to control M5stack roverc pro with M5stickC Plus2 using a bluetooth terminal to send commands via Bluetooth
//I used Arduino Ide to program M5stickC Plus2 . 
//Install necessary libraries like M5stickCPlus2, BluetooothSerial and M5RoverC
#include <M5StickCPlus2.h>
#include <M5_RoverC.h>
#include <BluetoothSerial.h>

M5_RoverC roverc;
BluetoothSerial SerialBT;

void setup() {
    M5.begin();
    Serial.begin(115200); // Serial communication for debugging

    // Initialize Bluetooth
    if (!SerialBT.begin("M5StickCPlus2")) {
        Serial.println("An error occurred initializing Bluetooth");
    } else {
        Serial.println("Bluetooth initialized");
    }

    // Display instructions on the screen
    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Send commands via BT");

    // Initialize RoverC
    roverc.begin();
    roverc.setSpeed(0, 0, 0); // Start with rover stopped
}

void loop() {
    M5.update();

    // Handle Bluetooth commands
    if (SerialBT.available()) {
        char command = SerialBT.read();

        switch (command) {
            case 'f': 
                // Move rover forward
                roverc.setSpeed(100, 0, 0);
                break;
            case 'b':
                // Move rover backward
                roverc.setSpeed(-100, 0, 0);
                break;
            case 'l':
                // Move rover left
                roverc.setSpeed(0, 100, 0);
                break;
            case 'r':
                // Move rover right
                roverc.setSpeed(0, -100, 0);
                break;
            case 'a':
                // Rotate rover clockwise
                roverc.setSpeed(0, 0, 100);
                break;
            case 'c':
                // Rotate rover counterclockwise
                roverc.setSpeed(0, 0, -100);
                break;
            default:
                // Stop the rover if an unrecognized command is received
                roverc.setSpeed(0, 0, 0);
                break;
        }

        // Display the received command on M5StickC Plus2's screen
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.println("Received: " + String(command));
    }

    delay(300); // Adjust delay as needed for responsiveness
}
