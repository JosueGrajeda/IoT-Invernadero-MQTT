# IoT-Invernadero-MQTT 

Este repositorio contiene los códigos de programación implementados para un sistema IoT de invernadero, utilizando **ESP32** y comunicación **MQTT**.  
Incluye scripts en **Python** para el publicador y suscriptor, así como módulos en **C++/Arduino** para la lógica del controlador.

---

##  Estructura del proyecto

- **python/**  
  Scripts en Python para:
  - `envio-datos-mqtt.py`: Publicador MQTT.
  - `suscriptor-datos-mqtt.py`: Suscriptor MQTT.

- **cpp_arduino/**  
  Código en C++ y Arduino:
  - `ADC.cpp`, `GPIO.cpp`, `MENU.cpp`, `PRINT.cpp`, `SIST_EXPERTO.cpp`: Módulos de lógica y periféricos.
  - `BSP.h`: Cabecera principal.
  - `MQTT.cpp`: Implementación de cliente MQTT en ESP32.
  - `TBlanco_invernadero.ino`: Programa principal para el invernadero.

---

##  Uso

1. Clona el repositorio:
   ```bash
   git clone https://github.com/JosueGrajeda/IoT-Invernadero-MQTT.git
