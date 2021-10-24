import pandas as pd
from openpyxl import Workbook
import csv
import time 
import serial

nome = str(input("Planta:", ))

arduino = serial.Serial("COM3", 9600)
temperatura = []
umidade = []
luminosidade = []
umidade_solo = []
min_20 = 1200 
seg_2 = 2 
quantidade_de_dados = 72
def Csv():
    dados = {" T ": temperatura , 
             " Ar ": umidade ,
             "Solo": umidade_solo,
             "Luz": luminosidade}

    df = pd.DataFrame(data= dados)
    return df.to_csv(f"{nome}.csv", index=False)

def Excel():
    
    wb = Workbook()
    ws = wb.active
    with open(f'{nome}.csv', 'r') as f:
        for row in csv.reader(f):
            ws.append(row)

    return wb.save(f'{nome}.xlsx')


def Format(nome, x):
    code = nome.decode()
    trip = code.strip()
    valor = x(trip)
    return valor



for i in range(1):
    while i != quantidade_de_dados:
        
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

        time.sleep(seg_2)

        temperatura.append(t_)
        umidade.append(u_)
        umidade_solo.append(s_)
        luminosidade.append(l_)
        Csv()
        Excel()

        time.sleep(min_20)

        i+=1