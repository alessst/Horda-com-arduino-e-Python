import time
import serial

arduino = serial.Serial("COM3", 9600)

def Format(nome , v):
    code = nome.decode()
    trip = code.strip()
    inteiro = v(trip)
    return inteiro

while True:
    u = arduino.readline()
    t = arduino.readline()
    s = arduino.readline()
    l = arduino.readline()

    u_ = Format(u, float)
    t_ = Format(t, float)
    s_ = Format(s, int)
    l_ = Format(l, int)
    
    print("-------------------------------")
    print(f"Umidade Ambiente: {u_}")
    print(f"Temperatura Ambiente:{t_}")
    print(f"Umidade do Solo: {s_}")
    print(f"Luminosidade: {l_}")
    print("-------------------------------")

    time.sleep(5)