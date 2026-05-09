/********************************************************
  Instituto Tecnológico de Chihuahua
  TAREA 1: SISTEMAS EXPERTOS
  Dispositivo para un invernadero/habitación
  Sistema Embebido de Control de Confort y Seguridad
  Equipo Blanco: Gerardo Almeida Bermúdez 22061097
                 Josué Saul Grajeda Manríquez 21060696
*********************************************************/

#include "BSP.h"

/******************** VARIABLES GLOBALES ****************/

float temp = 0, setTemp = 0;
int ldr_valor = 0;
int H_memoria = 0;

SemaphoreHandle_t dataMutex;

/******************** FUNCIONES AUXILIARES **************/

float mapearTemp(int valor) //Facilita conversión de temperatura con ADC a 12 bits en el ESP32
{return (valor * 300.0) / 4095.0;}

float mapearPot(int valor) //Facilita conversión del potenciometro con ADC a 12 bits en el ESP32
{return (valor * 23.0) / 4095.0;}

/******************** TAREA - LECTURA ********************/

void TaskLeerSensores(void *pvParameters)
{
  while (1)
  {
    if (sistema_modo)
    {
      xSemaphoreTake(dataMutex, portMAX_DELAY);

      temp = mapearTemp(ADC_read(TEMP_PIN));
      setTemp = mapearPot(ADC_read(POT_PIN));
      ldr_valor = ADC_read(LDR_PIN);

      xSemaphoreGive(dataMutex);
    }

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

/******************** TAREA - MQTT ********************/

void TaskMQTT(void *pvParameters) {
  while (1) {
    MQTT_loop();
    if (sistema_modo) {
      xSemaphoreTake(dataMutex, portMAX_DELAY);
      String payload = "{";
      payload += "\"temp\":" + String(temp) + ",";
      payload += "\"set\":" + String(setTemp) + ",";
      payload += "\"ldr\":" + String(ldr_valor) + "}";
    if (!MQTT_publish(payload)) {
    Serial.println("Error: No se pudo publicar en MQTT.");
   }
      xSemaphoreGive(dataMutex);
  }
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}

/******************** TAREA - CONSOLA  ******************/

void TaskConsola(void *pvParameters)
{
  while (1)
  {
    if (sistema_modo)
    {PRINT_data();}

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

/******************** TAREA - SISTEMA EXPERTO ************/

void TaskExperto(void *pvParameters)
{
  while (1)
  {
    if (sistema_modo)
    {SistemaExperto_run();}

    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

/******************** TAREA BOTON  *********************/

void TaskBoton(void *pvParameters) {
  int estadoFinal = LOW;
  while (1) {
    bool estadoActual = GPIO_read(BOTON_PIN);
    if (estadoActual == LOW && estadoFinal == HIGH) {
      vTaskDelay(200 / portTICK_PERIOD_MS);
      if (GPIO_read(BOTON_PIN) == LOW) {
        sistema_modo = !sistema_modo;
        GPIO_write(LED_STATUS, sistema_modo);
        Serial.println(sistema_modo ? "Sistema ACTIVADO" : "Sistema DESACTIVADO");
      }
    }
    estadoFinal = estadoActual;
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

/******************** SETUP *********************/

void setup()
{ Serial.begin(9600); // Inicializa la comunicación serial
  
  // Ajusta el tiempo máximo de espera de Serial.readStringUntil()
  Serial.setTimeout(60000); // espera hasta 1 minuto antes de avanzar

  Menu_run(); // Ejecuta el menú de configuración al inicio

  // Inicialización de módulos
  ADC_init();
  GPIO_init();
  PRINT_init();

  //Inicialización del Broker MQTT: Conexión a red WiFi, servidor y puerto
  MQTT_begin();

  dataMutex = xSemaphoreCreateMutex();

  // Creación de tareas RTOS
  xTaskCreatePinnedToCore(TaskLeerSensores, "LeerSensores", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskConsola, "Consola", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskExperto, "Experto", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskBoton, "Boton", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskMQTT, "MQTT", 4096, NULL, 1, NULL, 1);
}

void loop()
{
  // No se requiere, RTOS (Mediante FreeRTOS) 
  // realiza la gestión de todo el sistema a traves de tareas y un mutex
}