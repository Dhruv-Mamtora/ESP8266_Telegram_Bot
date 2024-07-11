/*
 * ESP8266 Telegram Bot with DHT11 Sensor
 * 
 * Author: Dhruv Mamtora(https://github.com/Dhruv-Mamtora)
 * Date: July 11, 2024
 * 
 * Description:
 * This project demonstrates how to use an ESP8266 microcontroller with a DHT11 sensor to monitor temperature and humidity.
 * It allows interaction with the user via a Telegram bot. The bot can respond to commands to get the current temperature and humidity.
 * 
 * Components Required:
 * - ESP8266 microcontroller
 * - DHT11 temperature and humidity sensor
 * - WiFi connection
 * 
 * Libraries Used:
 * - ESP8266WiFi: For WiFi connectivity
 * - WiFiClientSecure: For secure HTTPS requests
 * - UniversalTelegramBot: For interacting with Telegram Bot API
 * - DHT: For reading temperature and humidity from the DHT11 sensor
 * 
 * Configuration:
 * - Replace `YOUR_SSID` with your WiFi network's SSID
 * - Replace `YOUR_PASSWORD` with your WiFi network's password
 * - Replace `YOUR_BOT_TOKEN` with your Telegram bot token
 * - Replace `YOUR_CHAT_ID` with your Telegram chat ID
 * 
 * Note:
 * - `client.setInsecure()` is used to disable SSL certificate validation. For production use, implement proper SSL certificate validation.
 * - Ensure sensitive information like bot tokens and chat IDs are not shared publicly.
 * 
 * Commands:
 * - /temperature: Get the current temperature from the DHT11 sensor
 * - /humidity: Get the current humidity from the DHT11 sensor
 * - /start: Get a welcome message with available commands
 * 
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>

// Network credentials (replace with your own)
char ssid[] = "YOUR_SSID";          // Your WiFi network SSID (name)
char password[] = "YOUR_PASSWORD"; // Your WiFi network password

// Telegram Bot configuration (replace with your own)
#define BOTtoken "YOUR_BOT_TOKEN"  // Your Telegram bot token
#define ID "YOUR_CHAT_ID" // Your Telegram chat ID 

// DHT sensor configuration
#define DHT_TYPE DHT11         // Define the type of DHT sensor
#define DHT_PIN 5              // Define the pin connected to the DHT sensor (D1 on NodeMCU)

DHT dht(DHT_PIN, DHT_TYPE); // Create an instance of the DHT sensor

WiFiClientSecure client;                   // Create a WiFiClientSecure object for HTTPS requests
UniversalTelegramBot bot(BOTtoken, client); // Create a Telegram Bot instance

int botRequestDelay = 1000; // Delay between bot requests to Telegram (1 second)
unsigned long lastTimeBotRan; // Timestamp of the last bot run

/**
 * Handle incoming messages from Telegram
 * @param numNewMessages Number of new messages received
 */
void handleNewMessages(int numNewMessages)
{
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = String(bot.messages[i].chat_id); // Get chat ID
    String text = bot.messages[i].text; // Get message text
    String from_name = bot.messages[i].from_name; // Get sender's name

    if (chat_id == ID) // Check if the message is from the authorized user
    {
      if (text == "/temperature")
      {
        // Read temperature from DHT11 sensor
        float temperature = dht.readTemperature();
        if (isnan(temperature))
        {
          bot.sendMessage(chat_id, "Failed to read temperature!", "");
        }
        else
        {
          String temp = "Temperature: ";
          temp += String(temperature);
          temp += "°C";
          bot.sendMessage(chat_id, temp, "");
        }
      }
      else if (text == "/humidity")
      {
        // Read humidity from DHT11 sensor
        float humidity = dht.readHumidity();
        if (isnan(humidity))
        {
          bot.sendMessage(chat_id, "Failed to read humidity!", "");
        }
        else
        {
          String hum = "Humidity: ";
          hum += String(humidity);
          hum += "%";
          bot.sendMessage(chat_id, hum, "");
        }
      }
      else if (text == "/start")
      {
        // Send welcome message with available commands
        String welcome = "Welcome  " + from_name + "\n\nThis bot is built by Dhruv to find room temperature.\n\nChoose your option:\n";
        welcome += "/temperature : Get Temperature\n";
        welcome += "/humidity : Get Humidity\n";
        bot.sendMessage(chat_id, welcome, "Markdown");
      }
    }
    else
    {
      // Send unauthorized message if the user is not authorized
      bot.sendMessage(chat_id, "Unauthorized User", "");
    }
  }
}

void setup()
{
  Serial.begin(115200);  // Start serial communication at 115200 baud rate
  client.setInsecure();  // Disable SSL certificate validation for HTTPS (not recommended for production)

  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("Connecting WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize DHT sensor
  dht.begin();
}

void loop()
{
  if (millis() > lastTimeBotRan + botRequestDelay)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("Got Response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
