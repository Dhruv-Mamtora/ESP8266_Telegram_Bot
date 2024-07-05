# ESP8266 Telegram Bot for DHT Sensor

This project sets up an ESP8266 microcontroller to work as a Telegram bot. It reads temperature and humidity data from a DHT11 sensor and responds to specific commands from authorized users.

## Prerequisites
- Arduino IDE with ESP8266 support
- Libraries: ESP8266WiFi, WiFiClientSecure, UniversalTelegramBot, DHT

## Configuration
1. Replace placeholders in `main.ino`:
   - `ssid` with your WiFi SSID
   - `password` with your WiFi password
   - `BOTtoken` with your Telegram bot token
   - `chat_id` with the authorized user's chat ID

## Commands
- `/start` - Initialize the bot and get commands list.
- `/temperature` - Get current room temperature.
- `/humidity` - Get current room humidity.

## Setup
1. Upload the sketch to your ESP8266 board using Arduino IDE.
2. Open Serial Monitor to view debug messages.
3. Interact with the bot on Telegram.

