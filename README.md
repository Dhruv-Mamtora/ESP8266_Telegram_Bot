# ESP8266 Telegram Bot

This project demonstrates how to use an ESP8266 with a DHT11 sensor to monitor temperature and humidity, and interact with users via a Telegram bot.

## Requirements

- ESP8266 board
- DHT11 sensor
- Libraries:
  - `ESP8266WiFi`
  - `WiFiClientSecure`
  - `UniversalTelegramBot`
  - `DHT`

## Setup

### 1. Install Libraries

Install the required libraries through the Arduino Library Manager:

1. Open the Arduino IDE.
2. Go to `Sketch` > `Include Library` > `Manage Libraries...`.
3. Search for and install the following libraries:
   - **ESP8266WiFi**: Provides support for the ESP8266 WiFi module.
   - **WiFiClientSecure**: Provides secure HTTPS client functionality.
   - **UniversalTelegramBot**: Allows interaction with the Telegram Bot API.
   - **DHT**: Provides functions to read data from the DHT sensor.

Alternatively, you can download the libraries manually and place them in the `libraries` folder of your Arduino sketchbook. Here are the links to download them:

- [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
- [WiFiClientSecure](https://github.com/esp8266/Arduino/tree/master/libraries/WiFiClientSecure)
- [UniversalTelegramBot](https://github.com/mobizt/ArduinoJson)
- [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)

### 2. Configure Credentials

You need to set up a Telegram bot and obtain your bot token and chat ID. Follow these steps to create and configure your bot:

#### Create a Telegram Bot

1. Open Telegram and search for the "[BotFather](https://t.me/BotFather)" bot.
2. Start a chat with BotFather and use the command `/newbot`.
3. Follow the prompts to create a new bot and obtain the bot token.
Replace `<YOUR_BOT_TOKEN>` with the token you received from BotFather.

#### Find Your Chat ID

1. Start a chat with [your bot](https://t.me/myidbot) on Telegram.
2. Send `/getid` message to the bot.
Replace `<YOUR_CHAT_ID>` with the ID you received from [your bot](https://t.me/myidbot).

Replace the placeholders in the code with your credentials:
- `YOUR_SSID` with your WiFi network SSID.
- `YOUR_PASSWORD` with your WiFi network password.
- `YOUR_BOT_TOKEN` with your Telegram bot token.
- `YOUR_CHAT_ID` with your Telegram chat ID.

### 3. Upload Code

1. Open the Arduino IDE.
2. Copy and paste the provided code into a new sketch.
3. Connect your ESP8266 board to your computer via USB.
4. Select the correct board and port from the `Tools` menu.
5. Click on the `Upload` button to compile and upload the code to your ESP8266 board.

### 4. Monitor Output

1. After uploading the code, open the Serial Monitor in the Arduino IDE (`Tools` > `Serial Monitor`).
2. Set the baud rate to `115200`.
3. Monitor the Serial Monitor for connection status and received commands.

## Commands

- `/temperature` - Get the current temperature from the DHT11 sensor.
- `/humidity` - Get the current humidity from the DHT11 sensor.
- `/start` - Get a welcome message with available commands.

## Notes

- The bot token and chat ID should be kept private. Consider using environment variables or a secure method to manage these credentials in a real-world application.
- `client.setInsecure()` is used to disable SSL certificate validation. For production use, implement proper SSL certificate validation.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
