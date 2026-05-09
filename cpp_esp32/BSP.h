/********************************************************
  Instituto Tecnológico de Chihuahua
  TAREA 1: SISTEMAS EXPERTOS
  Archivo: BSP.h
  Equipo Blanco: Gerardo Almeida Bermúdez 22061097
                 Josué Saul Grajeda Manríquez 21060696
*********************************************************/

#ifndef BSP_H
#define BSP_H

/****************** LIBRERIAS ******************/

#include <Arduino.h>      //Necesaria para uso en Arduino IDE
#include <WiFi.h>         //Referente hacia el uso y configuracion de redes inalambricas Wifi
#include <PubSubClient.h> //Referente a Clientes Publicador-Suscriptor
#include <WebServer.h>    //Referente al empleo de interfaz web
#include <Preferences.h>  //Referente al fuardado de datos como "preferencias"

//Necesarias al plantearse bajo el esquema de ESP-IDF
#include <stdio.h>   
#include <stdbool.h>
#include "driver/adc.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

/****************** PINES ******************/

#define LED_STATUS GPIO_NUM_2  //GPIO 2
#define LED_A1     GPIO_NUM_4  //GPIO 4
#define LED_A2     GPIO_NUM_5  //GPIO 5
#define LED_A3     GPIO_NUM_18 //GPIO 18
#define LED_A4     GPIO_NUM_19 //GPIO 19

#define BOTON_PIN  GPIO_NUM_15 //GPIO 15

#define LDR_PIN ADC1_CHANNEL_6  //GPIO34
#define TEMP_PIN ADC1_CHANNEL_5 //GPIO33
#define POT_PIN ADC1_CHANNEL_4  //GPIO32

/****************** UMBRALES ******************/

//#define LOW 0
//#define HIGH 1
#define U1 1000
#define U2 3000
#define DELTA 1

/****************** VARIABLES GLOBALES ******************/

extern volatile bool sistema_modo;

extern float temp;
extern float setTemp;
extern int ldr_valor;
extern int H_memoria;

extern SemaphoreHandle_t dataMutex;

/****************** PROTOTIPOS ******************/

void ADC_init(void);
int ADC_read(adc1_channel_t channel);

void GPIO_init(void);
void GPIO_write(gpio_num_t pin, int value);
int GPIO_read(gpio_num_t pin);

void PRINT_init(void);
void PRINT_data(void);

void SistemaExperto_run(void);

// ====== FUNCIONES MQTT/WIFI ======
void saveConfig();
void loadConfig();
void MQTT_begin();
void MQTT_loop();
bool MQTT_publish(String payload);

// ====== FUNCIONES MENU ======
void Menu_run();

#endif