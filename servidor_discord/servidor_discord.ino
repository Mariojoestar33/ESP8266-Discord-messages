#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Discord_WebHook.h>

const char *ssid = "INFINITUM2060";
const char *password = "Chispaxd10";
Discord_Webhook discord;
String DISCORD_WEBHOOK = "https://discord.com/api/webhooks/1184306215220674651/4GyZQ01NwQ0Aiq98KTgJQKhgCEZ3C8v4A6sF8QxitoMzJFEHJKlfg_rE_HfFT_HoxD-G";
const int lm35Pin = A0;

ESP8266WebServer server(80);

const int ledPin = 2;

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado a la red WiFi");

  Serial.println("Información de la conexión:");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Red: ");
  Serial.println(WiFi.SSID());

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "¡Hola desde ESP8266!");
  });

  server.on("/encender", HTTP_GET, []() {
    analogWrite(ledPin, 0);
    server.send(200, "text/plain", "LED encendido");
    sendDiscordMessage("¡El LED ha sido encendido!");
  });

  server.on("/apagar", HTTP_GET, []() {
    analogWrite(ledPin, 1023);
    server.send(200, "text/plain", "LED apagado");
    sendDiscordMessage("¡El LED ha sido apagado!");
  });

  server.on("/info", HTTP_GET, []() {
    String info = "IP: " + WiFi.localIP().toString() + "\n";
    info += "Red: " + WiFi.SSID() + "\n";
    server.send(200, "text/plain", info);
  });

  server.on("/encenderFoco", HTTP_GET, []() {
    server.sendHeader("Location", "http://192.168.0.115:5000/bulbon", true);
    sendDiscordMessage("¡Has prendido el foco de la habitación!");
    server.send(302, "text/plain", "");
  });

  server.on("/apagarFoco", HTTP_GET, []() {
    server.sendHeader("Location", "http://192.168.0.115:5000/bulboff", true);
    sendDiscordMessage("¡Has apagado el foco de la habitación!");
    server.send(302, "text/plain", "");
  });

  server.begin();
}

void loop() {
  server.handleClient();

  float temperature = analogRead(lm35Pin) + 6;

  Serial.println("La temperatura es de: " + String(temperature)+ "°C!!!");

  if(temperature > 25) {
    String mensaje = "La temperatura esta rebasando el limite permitido (19°C) - Temperatura actual: " + String(temperature)+ "°C";
    sendDiscordMessage(mensaje);
  }

  delay(1000);
}

void sendDiscordMessage(String message) {
  discord.begin(DISCORD_WEBHOOK);
  discord.addWiFi(ssid, password);
  discord.connectWiFi();
  bool message_sent = discord.send(message); 
  if(message_sent) {
    Serial.println("Mensaje :" +message+ " enviado satisfactoriamente!!!");
  } else {
    Serial.println("ERROR AL ENVIAR MENSAJE");
  }
}