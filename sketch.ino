#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient WOKWI_Client;
PubSubClient client(WOKWI_Client);

#define ONE_WIRE_BUS 4 // Pino do DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Definições do Potenciômetro
#define POT_PIN 32 // Pino do Potenciômetro (ADC)

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
   
    // Attempt to connect
    if (client.connect("WOKWI_Client")) {
      Serial.println("connected");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  sensors.begin();
}



void loop() {
    reconnect();

    client.loop();

    // Lê a temperatura do DS18B20
    sensors.requestTemperatures();
    float tempDS18B20 = sensors.getTempCByIndex(0);
    Serial.print("Temperatura DS18B20: ");
    Serial.println(tempDS18B20);

    // Lê o valor do potenciômetro
    int potValue = analogRead(POT_PIN); // Lê o valor do potenciômetro
    Serial.print("Valor do Potenciômetro: ");
    Serial.println(potValue);

    // Opcional: converte o valor do potenciômetro para um percentual (0-100%)
    float potPercent = (potValue / 1023.0) * 100.0;
    Serial.print("Potência Ajustada: ");
    Serial.print(potPercent);
    Serial.println("%");

    // Cria um payload JSON
    String payload = "{\"Temperatura\":" + String(tempDS18B20) + ",\"Potenciometro\":" + String(potPercent) + "}";

    // Publica o payload no tópico desejado
    client.publish("esp32", payload.c_str());

    delay(2000); // Aguarda 2 segundos antes da próxima leitura

}