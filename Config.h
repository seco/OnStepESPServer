// -------------------------------------------------------------------------------
// Configuration

#define DEBUG_OFF           // Turn ON to allow WiFi startup without OnStep attached (Serial port for debug at 115200 baud)

// Note: OnStep Serial1 interface (at 9600 baud) must be attached and running...
//       At startup this firmware will attempt to switch to the baud rate below and AFTER success, start WiFi, etc.
#define SERIAL_BAUD ":SB1#" // 0=115.2K, 1=57.6K, 2=38.4K Baud, 3=28.8K, 4=19.2K Baud ... Default ":SB1#", if talking to a Mega2560 ":SB4#"
#define SERIAL_SWAP_OFF     // Default=OFF, ON to swap ESP8266 Serial default location GPIO 1(TX)/3(RX) to 15(TX)/13(RX) useful for WeMos D1 Mini, for example

// The settings below are for initialization only, afterward they are stored and recalled from EEPROM and must
// be changed in the web interface OR with a reset (for initialization again) as described in the comments below
#define TIMEOUT_WEB 15      // Default=15, if talking to a Mega2560 double the default
#define TIMEOUT_CMD 30      // Default=30, if talking to a Mega2560 double the default

// On first startup an AP will appear with an SSID of "ONSTEP", after connecting:
// The web-site is at "192.168.0.1" and the cmd channel is at "192.168.0.1:9999".
//
// If locked out of the ESP8266, a Sketch (like MultiSerial) uploaded to the OnStep MCU (Teensy3.2, Launchpad, etc.) can recover access.
// Simply sending an 'R' in reply to any '#' received will cause a reset to AP only enabled and the default SSID/Password.  Be sure to
// upload OnStep again and then restart both devices to resume operation.

// -------------------------------------------------------------------------------

