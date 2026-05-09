#include "BSP.h"

extern Preferences prefs; // reutilizamos prefs de MQTT.cpp

void mostrarMenu() {
  Serial.println("===== MENU PRINCIPAL =====");
  Serial.println("n -> Nueva configuración");
  Serial.println("l -> Cargar configuración");
  Serial.println("c -> Borrar configuración");
  Serial.print("Seleccione una opción: ");
}

void Menu_run() {
  mostrarMenu();
  // Leer la opción completa (hasta Enter)
  String opcionStr = Serial.readStringUntil('\n');
  opcionStr.trim(); // quitar espacios o saltos extra
  char opcion = opcionStr.charAt(0);

  Serial.print("Opción seleccionada: ");
  Serial.println(opcion);

  switch(opcion) {
    case 'n':{
      Serial.println("\nNueva configuración seleccionada.");

      Serial.println("Ingrese SSID:");
      String ssid = Serial.readStringUntil('\n');
      ssid.trim();
      if (ssid.equalsIgnoreCase("d")) { Serial.println("Cancelado."); return; }
      Serial.print("SSID capturado: "); Serial.println(ssid);

      Serial.println("Ingrese Password:");
      String pass = Serial.readStringUntil('\n');
      pass.trim();
      if (pass.equalsIgnoreCase("d")) { Serial.println("Cancelado."); return; }
      Serial.print("Password capturado: "); Serial.println(pass);

      Serial.println("Ingrese Broker IP:");
      String broker = Serial.readStringUntil('\n');
      broker.trim();
      if (broker.equalsIgnoreCase("d")) { Serial.println("Cancelado."); return; }
      Serial.print("Broker capturado: "); Serial.println(broker);

      Serial.println("Ingrese Usuario MQTT:");
      String user = Serial.readStringUntil('\n');
      user.trim();
      if (user.equalsIgnoreCase("d")) { Serial.println("Cancelado."); return; }
      Serial.print("Usuario MQTT capturado: "); Serial.println(user);

      Serial.println("Ingrese Password MQTT:");
      String mqttpass = Serial.readStringUntil('\n');
      mqttpass.trim();
      if (mqttpass.equalsIgnoreCase("d")) { Serial.println("Cancelado."); return; }
      Serial.print("Password MQTT capturado: "); Serial.println(mqttpass);

      // Guardar configuración usando prefs
      prefs.begin("config", false);
      prefs.putString("ssid", ssid);
      prefs.putString("pass", pass);
      prefs.putString("broker", broker);
      prefs.putString("user", user);
      prefs.putString("mqttpass", mqttpass);
      prefs.putInt("port", 1883);
      prefs.end();

      Serial.println("Configuración guardada correctamente.");
      break;
    }
    case 'l':{
      Serial.println("\nCargando configuración previa...");
      loadConfig();
      break;
    }
    case 'c': {
      Serial.println("\nBorrando configuración...");
      prefs.begin("config", false);
      prefs.clear();   // elimina todo lo guardado
      prefs.end();
      Serial.println("Configuración borrada correctamente.");
      ESP.restart();   // reinicia para arrancar limpio
      break;
    }
    default:{
      Serial.println("\nOpción inválida. Reiniciando ESP32...");
      ESP.restart();
      break;
    }
  }
}