/********************************************************
  Instituto Tecnológico de Chihuahua
  TAREA 1: SISTEMAS EXPERTOS
  Archivo: PRINT.cpp
  Equipo Blanco: Gerardo Almeida Bermúdez 22061097
                 Josué Saul Grajeda Manríquez 21060696
*********************************************************/

#include "BSP.h"

// Inicialización de la Consola: Componente para comunicacióm por terminal (Serial)
void PRINT_init(void)
 {  
    Serial.println("ESP32 iniciado...");
    Serial.println("Sistema de control de confort y seguridad");
    Serial.println("------------------------------------------");
 }

// Configuración para impresión de las lecturas actuales del sistema 
void PRINT_data(void)
 {
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" °C | ");

    Serial.print("SetTemp: ");
    Serial.print(setTemp);
    Serial.print(" °C | ");

    Serial.print("LDR: ");
    Serial.print(ldr_valor);
    Serial.print(" | ");

    Serial.println();
 }