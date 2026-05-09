/********************************************************
  Instituto Tecnológico de Chihuahua
  TAREA 1: SISTEMAS EXPERTOS
  Archivo: MQTT.cpp
  Equipo Blanco: Gerardo Almeida Bermúdez 22061097
                 Josué Saul Grajeda Manríquez 21060696
*********************************************************/

#include "BSP.h"

WiFiClient espClient;
PubSubClient client(espClient);
WebServer server(80);
Preferences prefs;

// ===== Variables configurables =====
String ssid, password, mqtt_server, mqtt_user, mqtt_pass;
int mqtt_port = 1883;

const char* topicData = "invernadero/data";
const char* topicControl = "invernadero/control"; 

volatile bool sistema_modo = false; // Variable global para controlar el estado del sistema

// ===== Guardar / cargar =====
void loadConfig() {
  prefs.begin("config", true);
  ssid = prefs.getString("ssid", "");
  password = prefs.getString("pass", "");
  mqtt_server = prefs.getString("broker", "");
  mqtt_user = prefs.getString("user", "");
  mqtt_pass = prefs.getString("mqttpass", "");
  mqtt_port = prefs.getInt("port", 1883);
  prefs.end();

  Serial.println("=== Configuración cargada ===");
  Serial.print("SSID: "); Serial.println(ssid);
  Serial.print("Broker: "); Serial.println(mqtt_server);
  Serial.print("Usuario: "); Serial.println(mqtt_user);
  Serial.print("Password: "); Serial.println(mqtt_pass);
  Serial.print("Puerto: "); Serial.println(mqtt_port);
}

void saveConfig() {
  prefs.begin("config", false);
  prefs.putString("ssid", ssid);
  prefs.putString("pass", password);
  prefs.putString("broker", mqtt_server);
  prefs.putString("user", mqtt_user);
  prefs.putString("mqttpass", mqtt_pass);
  prefs.putInt("port", mqtt_port);
  prefs.end();
}

// ====== MQTT: CALLBACK y RECONNECT ======
void callback(char* topic, byte* payload, unsigned int length) {
  String mensaje;

  for (int i = 0; i < length; i++) {
    mensaje += (char)payload[i];
  }

  mensaje.trim();

  Serial.print("Mensaje recibido en tópico [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(mensaje);

  // Procesar ON / OFF
  if (mensaje.equalsIgnoreCase("ON")) {
    sistema_modo = true; GPIO_write(LED_STATUS, sistema_modo);
    Serial.println("Sistema ACTIVADO por MQTT.");
    // Aquí puedes iniciar tareas, sensores, etc.
  } else if (mensaje.equalsIgnoreCase("OFF")) {
    sistema_modo = false; GPIO_write(LED_STATUS, sistema_modo);
    Serial.println("Sistema DESACTIVADO por MQTT.");
    // Aquí puedes detener tareas, sensores, etc.
  } else {
    Serial.println("Comando desconocido, ignorado.");
  }
}

void reconnect() 
{
  while (!client.connected()) {
    if (client.connect("ESP32Client", mqtt_user.c_str(), mqtt_pass.c_str())) {
      Serial.println("Conectado al broker MQTT.");
      client.subscribe(topicControl);
      Serial.print("Suscrito al tópico: ");
      Serial.println(topicControl);
    } else {
      Serial.print("Error de conexión MQTT, código: ");
      Serial.println(client.state());
      delay(5000);

    }
  }
}

// ====== MQTT: INICIALIZACION - LOOP - PUBLISH ======
void MQTT_begin() 
{
   loadConfig();

  // Si no hay config → modo AP
  if (ssid == "" || mqtt_server == "") {
    Serial.println("No hay configuración guardada. Use el menú serial para ingresar datos.");
    ESP.restart(); // reinicia para que el usuario entre al menú
    //startAPConfig();
  }

  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  client.setServer(mqtt_server.c_str(), mqtt_port);
  client.setCallback(callback);
}

void MQTT_loop() {
  if (!client.connected()) reconnect();
  client.loop();
}

bool MQTT_publish(String payload) {
  return client.publish(topicData, payload.c_str());
}