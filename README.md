# OnStepESPServer

This is the ESP8266-01 webserver for OnStep.  It provides WiFi (IP) access to connect to OnStep via command channel and/or website.  This works with Sky Safari (tablets/phones,) my OnStep Android App, and my ASCOM driver (PC.)

Configure the ESP8266-01 using the wiring as shown in numerous places on the internet to get the module in firmware upload mode.
To send the firmware I use the Arduino 1.6.9 IDE with the add-on for the ESP8266.  To get this setup...

Look in the Arduino Preferences menu and place this line in the additional "Boards Manager" area:
http://arduino.esp8266.com/staging/package_esp8266com_index.json
Then from the "Tools->Boards->Boards Manager" menu select the ESP8266 add-on.

Then pick "Tools->Boards->Generic 8266 Module".

Download the OnStepESPServer.zip file from GitHub.

Unzip the folder inside and rename it to "OnStepESPServer". This can be on your desktop or in your ~/Documents/Arduino folder.

Open the OnStepESPServer.ino file inside this folder and upload.


Read the source code comments for help configuring!  Once the firmware is on the module simply connect the serial interface lines to OnStep's Serial1 port similar to how a Bluetooth module would be connected.

I've only tested this with a Teensy3.2.  The Mega2560 may or may not work (probably not) and I don't support that option.  Launchpad TM4C's should be fine AFAIK, I THINK their 3.3v regulator is capable of powering an ESP8266.

