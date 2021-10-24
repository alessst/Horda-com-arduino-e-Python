#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
#define pinoAnalog A0 // Pino Umidade Solo
#define pinoRele 7 // Rele Irrigação Solo
#define pinoSensorLuz A2   // Sensor de Luz
#define pinoReleLuz 6 // Rele Luz
//#define porta_botao1 2 // aciona irrigação manualmente
//#define porta_botao2  3 // aciona luz manulamente


DHT dht(DHTPIN, DHTTYPE);

const byte SCREEN_WIDTH = 128; // OLED display width, in pixels
const byte SCREEN_HEIGHT = 64; // OLED display height, in pixels
int ValAnalogIn;
int valor_analogico = 0;
int valorLuz = 0;
////Armazena o valor lido dos botoes
//int leitura1 = 0;
//int leitura2 = 0;
////Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
//int estadorele1 = 1;
//int estadorele2 = 1;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
const int OLED_RESET = -1; // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()
{
  Serial.begin(9600);

  dht.begin();
  pinMode(pinoRele, OUTPUT);
  pinMode(pinoReleLuz, OUTPUT);
  //Define pinos dos botoes como entrada
  //  pinMode(porta_botao1, INPUT_PULLUP);
  //  pinMode(porta_botao2, INPUT_PULLUP);
  //Estado inicial dos reles - desligados
  digitalWrite(pinoRele, HIGH);
  digitalWrite(pinoReleLuz, HIGH);

  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear the buffer.
  display.clearDisplay();

  // Display Text "Hello Word"
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);


}

void loop() {
 
  display.clearDisplay();
  delay(50);
  display.setCursor(0, 0);
  display.print("Vegetable Garden!");
  
  Temp(); 
  
  Umidade();

  Irrigacao();
  
  Rele();

  display.display();
  

  

}

void Rele() {

  valorLuz = analogRead(pinoSensorLuz);
  int luminosidade = map(valorLuz, 1023, 0, 100, 0);
  Serial.println(luminosidade);
  //Serial.print("LUZ: ");
  //Serial.println(valorLuz);

  if (valorLuz >= 400)
  {
    digitalWrite(pinoReleLuz, HIGH);
    display.setCursor(0,56);
    display.print("Lamp Off!!");
    delay(10);
  }
  else
  {
    digitalWrite(pinoReleLuz, LOW);
    display.setCursor(0,56);
    display.print("Lamp On!");
    delay(10);
  }
 

}

void Irrigacao() {
  ValAnalogIn = analogRead(pinoAnalog); // Relaciona o valor analógico com o recebido do sensor
  int Porcento = map(ValAnalogIn, 1023, 0, 0, 100); // Relaciona o valor analógico à porcentagem
   Serial.println(Porcento);
 
  if (Porcento >= 40) { // Se a porcentagem for menor ou igual à
    display.setCursor(0, 46);
    display.print("Irrigating the plant"); // Imprime a frase no monitor serial
    digitalWrite(pinoRele, HIGH); // Altera o estado do pinoRele para nível Alto
    
  }

  else { // Se não ...
    display.setCursor(0, 46);
    display.print("Irrigated plant!"); // Imprime a frase no monitor serial
    digitalWrite(pinoRele, LOW); // Altera o estado do pinoRele para nível Baixo
  }
  delay (500); // Estabelece o tempo de 1s para reinicializar a leitura
}

void Temp() {
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    
    display.setCursor(0, 16);
    display.print("Moisture:");
    display.print(h);
    Serial.println(h);
    display.setCursor(0, 26);
    display.print("Temperature:");
    display.print(t);
    Serial.println(t);
    display.print(" C");
    delay(100);
    
  }
}


void Umidade() {
  //Le o valor do pino A0 do sensor
  valor_analogico = analogRead(pinoAnalog);

  //Solo umido, acende o led verde
  if (valor_analogico > 0 && valor_analogico < 500)
  {
    display.setCursor(0, 36);
    display.print("Wet soil");
    

  }

  //Solo com umidade moderada, acende led amarelo
  if (valor_analogico > 500 && valor_analogico < 600)
  {
    display.setCursor(0, 36);
    display.print("Moderate humidity");
    

  }
  //Solo seco, acende led vermelho
  if (valor_analogico > 600 && valor_analogico < 1024)
  {
    display.setCursor(0, 36);
    display.print("Dry soil");
    

  }
  delay(100);
}


// Acionamento com Botões
/*
  void button(){
  //Verifica o acionamento do botao 1
  leitura1 = digitalRead(porta_botao1);
  if (leitura1 != 0)
  {
    while (digitalRead(porta_botao1) != 0)
    {
      delay(100);
    }
    //Inverte o estado da porta
    estadorele1 = !estadorele1;
    //Comandos para o rele 1
    digitalWrite(pinoRele, estadorele1);
  }
  leitura2 = digitalRead(porta_botao2);
  if (leitura2 != 0)
  {
    while(digitalRead(porta_botao2) != 0)
    {
      delay(100);
    }
    //Inverte o estado da porta
    estadorele2 = !estadorele2;
    //Comandos para o rele 2
    digitalWrite(pinoReleLuz, estadorele2);
  }

  } */
