/*
 * MIT License
 *
 * Copyright (c) 2018 Donato Rimenti
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Program that reads messages incoming from serial port and sends them back.
 * Altough this program can manage any serial connection, it's been created
 * to test Bluetooth connections. In this scenario, the messages sent back 
 * may be split into multiple packets. This may be fixed in higher level 
 * protocols but for this example we simply don't care.
 * 
 * For the connection, Arduino TXD port goes to the Bluetooth device RXD port
 * and the Arduino RXD port goes to the Bluetooth device TXD port.
 * 
 * If you have any problems while transferring the program, try to unplug the
 * Arduino RXD port while doing it.
 */
String inputString = "";
char inChar;   

void setup() {
  // Starts the serial comunication.
  Serial.begin(9600);
}

void loop() {
    // Reads the input.
    while (Serial.available()) {
        inChar = (char) Serial.read(); 
        inputString += inChar;

        // Sends back the received string if any.
        if (inputString != "") {
            Serial.print(inputString);
            inputString = "";
        }
    }
}
