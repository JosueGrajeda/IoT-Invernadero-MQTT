/********************************************************
  Instituto Tecnológico de Chihuahua
  TAREA 1: SISTEMAS EXPERTOS
  Archivo: ADC.cpp
  Equipo Blanco: Gerardo Almeida Bermúdez 22061097
                 Josué Saul Grajeda Manríquez 21060696
*********************************************************/

#include "BSP.h"

// Inicialización y configuración propuesta para ADC 
void ADC_init(void)
 {
    adc1_config_width(ADC_WIDTH_BIT_12); // Resolución de 12 bits (0–4095)

    //Atenuacíon del ADC a 11dB (12dB): Permite medir un rango completo de 0 V a 3.3 V y evita saturar el ADC
    adc1_config_channel_atten(LDR_PIN, ADC_ATTEN_DB_12);
    adc1_config_channel_atten(TEMP_PIN, ADC_ATTEN_DB_12);
    adc1_config_channel_atten(POT_PIN, ADC_ATTEN_DB_12);
 }

// Lectura de cualquier pin ADC
int ADC_read(adc1_channel_t canal)
 {
   return adc1_get_raw(canal);
 }