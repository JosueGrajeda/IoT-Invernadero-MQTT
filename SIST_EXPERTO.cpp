/********************************************************
  Instituto Tecnológico de Chihuahua
  TAREA 1: SISTEMAS EXPERTOS
  Archivo: SIST_EXPERTO.cpp
  Equipo Blanco: Gerardo Almeida Bermúdez 22061097
                 Josué Saul Grajeda Manríquez 21060696
*********************************************************/

#include "BSP.h"

// Implementación y desarrollo de la lógica dada al sistema experto
void SistemaExperto_run(void)
 {
  float t, setT;
  int ldr;

  xSemaphoreTake(dataMutex, portMAX_DELAY);
  t = temp;
  setT = setTemp;
  ldr = ldr_valor;
  xSemaphoreGive(dataMutex);

  int D = 0; //Oscuridad
  int B = 0; //Brillantez
  int H;     //Caliente-Frio
  int S;     //Setpoint
  int A1, A2, A3, A4; //Salidas simuladas con LEDs

  // Clasificación de luz usando umbrales
  if (ldr < U1)
    {D = 1;} //Oscuro
  else if (ldr > U2)
    {B = 1;}  //Brillante

  // Banda o histéresis aplicada al rango de temperatura (Evita cambios rápidos de estado)
  if (t > (setT + DELTA))
    {H_memoria = 1;} //Caliente
  else if (t < (setT - DELTA))
    {H_memoria = 0;} //Frio

   H = H_memoria; // Para entendimiento entre manejo simbólico y su cambio en memoria

  // Clasificación de setpoint a temperatura ambiente como alto o bajo
  if (setT > 20)
    {S = 1;} //setTemp es alto
  else
    {S = 0;} //setTemp es bajo

  // Reglas del sistema experto NOTA: Se intercambian ecuaciones entre A2 y A3 por la lógica mencionada en el archivo de Tarea 1-IA
  A1 = D || (S && !B);            //Luz
  A2 = (!H) && S && (!B);         //Calefactor
  A3 = H || (!S && !D);           //Ventilador
  A4 = (D && B) || (H && S && B); //Alarma

  // Impresión de los estados para cada salida An (LEDs)
  GPIO_write(LED_A1, A1);
  GPIO_write(LED_A2, A2);
  GPIO_write(LED_A3, A3);
  GPIO_write(LED_A4, A4);
 }