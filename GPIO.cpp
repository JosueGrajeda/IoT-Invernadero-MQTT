/********************************************************
  Instituto Tecnológico de Chihuahua
  TAREA 1: SISTEMAS EXPERTOS
  Archivo: GPIO.cpp
  Equipo Blanco: Gerardo Almeida Bermúdez 22061097
                 Josué Saul Grajeda Manríquez 21060696
*********************************************************/

#include "BSP.h"

// Inicialización básica de GPIO: Abstracción de entradas y salidas digitales
void GPIO_init(void)
 {
    gpio_reset_pin(LED_STATUS);
    gpio_set_direction(LED_STATUS, GPIO_MODE_OUTPUT);

    gpio_reset_pin(LED_A1);
    gpio_reset_pin(LED_A2);
    gpio_reset_pin(LED_A3);
    gpio_reset_pin(LED_A4);

    gpio_set_direction(LED_A1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_A2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_A3, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_A4, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BOTON_PIN);
    gpio_set_direction(BOTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BOTON_PIN, GPIO_PULLUP_ONLY);
 }

// Configuración para lectura de bit (En el pin deseado)
int GPIO_read(gpio_num_t pin)
 {
   return gpio_get_level(pin);
 }

// Configuración para escritura de bit (En el pin deseado)
void GPIO_write(gpio_num_t pin, int valor)
 {
   gpio_set_level(pin, valor);
 }