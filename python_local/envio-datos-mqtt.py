#publicador mqtt
import paho.mqtt.client as mqtt
import time
import random

#definir parametros de conexion
#broker = "metzli.ddns.net"
broker = "192.168.1.34" #maquina virtual en IoT
usuario = "JOSUE"
passwd = "123"
port = 1883
#topic = "casa/habitacion/temperatura"
topic = "invernadero/temperatura"
topic2 = "invernadero/humedad"
topic3 = "invernadero/control"
intervalo = 5

# define callback
def on_connect(client, userdata, flag, rc):
    if(rc == 0):
        print(f"conectado al broker MQTT:{broker}")
    else:
        print(f"error al conectar al broker MQTT:{broker}")

#crear cliente MQTT
client = mqtt.Client()

#asignamos la funcion de callback para la conexion
client.on_connect =on_connect
client.username_pw_set(usuario, passwd)
#conectar al broker
client.connect(broker, port, 60)

#dejar la conexion en loop
client.loop_start()

#publicacion de la temperatura cada 5 segundos
led = "ON"
try:
    while True:
        temperatura = round(random.uniform(20,30),2)
        humedad = round(random.uniform(20,30),2)
        if led == "ON":
            led = "OFF"
        else:
            led = "ON"
        client.publish(topic, str(temperatura))
        client.publish(topic2, str(humedad))
        client.publish(topic3, led)
        time.sleep(intervalo)
except KeyboardInterrupt:
    print("Desconecxion del broker")
    client.loop_stop()
    client.disconnect()
    print(f"Desconectado del broker MQTT: {broker}")