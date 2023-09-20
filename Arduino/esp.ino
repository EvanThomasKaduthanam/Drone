#include <WiFi.h>

const char *ssid = "myNetwork";
const char *pass = "myPassword";

int status = WL_IDLE_STATUS;
const char *server = "your local ip"

    WiFiClient client;

void setup()
{
    Serial.begin(9600);

    status = WiFi.begin(ssid, pass);
    if (status != WL_CONNECTED)
    {
        Serial.println("Couldn't get a wifi connection");
    }
    else
    {
        Serial.println("Connected to wifi");
        Serial.println("\nStarting connection...");

        if (client.connect(servername, 9090))
        {
            Serial.println("connected");
        }
    }
}

void loop()
{
}