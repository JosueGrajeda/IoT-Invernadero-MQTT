#suscriptor mqtt

import paho.mqtt.client as mqtt

#definir parametros de conexion
#broker = "mqtt.rfc1918"
broker = "192.168.1.34"
usuario = "JOSUE"
passwd = "123"
#broker = "mqtt.iot.itchihuahua.mx"
port = 1883
#topic = "tec"
topic = "invernadero/temperatura"

# define callback
def on_connect(client, userdata, flag, rc):
    if rc == 0:
        print(f"onectado al broker MQTT {broker}")
        client.subscribe(topic)
        print(f"suscrito al topico: {topic}")
    else:
        print(f"error al conectar al broker MQTT")

def on_message(client, userdata, msg):
    print(f"mensaje recibido:{msg.payload.decode()}")

#crear cliente MQTT
client = mqtt.Client()
client.username_pw_set(usuario, passwd)
#asignamos la funcion de callback para la conexion
client.on_connect = on_connect
client.on_message = on_message

#conectar al broker
client.connect(broker, port, 60)

#dejar la conexion en loop
client.loop_forever()


