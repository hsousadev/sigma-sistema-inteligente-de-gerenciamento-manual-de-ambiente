/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

//Declarando as bibliotecas (node/blynk)
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Token de reconhecimento de tela
char auth1[] = "UdpdEXl-aagD7b2VFVF59jTcpnAcLEJo";

//Credenciais da internet (da rede)
char ssid[] = "RedeLuis";
char pass[] = "luisinho123";

//Botão Cozinha (V1/D7)
WidgetLED led1(V1);

//Botão Sala (V2/D8)
WidgetLED led2(V2);

//Botão Banheiro (V3/D0)
WidgetLED led3(V3);

//Botão Quarto (V4/D1)
WidgetLED led4(V4);

//Tempo de atualização do Blynk
BlynkTimer timer;

/////////DESLIGA/LIGA BOTÕES////////////
// COZINHA
void blinkLedWidget()
{
  if (led1.getValue()) {
    led1.off();
    Serial.println("LED on V1: off");
  } else {
    led1.on();
    Serial.println("LED on V1: on");
  }
// SALA
  if (led2.getValue()) {
    led2.off();
    Serial.println("LED on V2: off");
  } else {
    led2.on();
    Serial.println("LED on V2: on");
  }
  
// BANHEIRO
  if (led3.getValue()) {
    led3.off();
    Serial.println("LED on V3: off");
  } else {
    led3.on();
    Serial.println("LED on V3: on");
  }

// QUARTO
  if (led4.getValue()) {
    led4.off();
    Serial.println("LED on V4: off");
  } else {
    led4.on();
    Serial.println("LED on V4: on");
  }
}

/////////SLIDERS////////////
void fadeLedWidget()
{
  static int value = 0;
  static int delta = 30;
  value += delta;
  if (value > 255 || value < 0) {
    delta = -delta;
  } else {
    Serial.print("LED on: ");
    Serial.println(value);
    led1.setValue(value);
    led2.setValue(value);
    led3.setValue(value);
    led4.setValue(value);
  }
}
/////////NOTIFICAÇÕES////////////
void notifyUptime()
{
  long uptime = millis() / 60000L;

  // Actually send the message.
  // Note:
  //   We allow 1 notification per 15 seconds for now.
  Blynk.notify(String("Running for ") + uptime + " minutes.");
}


//Saída de dados
void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth1, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth1, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

//Saída de dados LED
  timer.setInterval(1000L, blinkLedWidget);
//Saída de dados Slide
  timer.setInterval(300L, fadeLedWidget);
//Saída de dados notificações
  timer.setInterval(60000L, notifyUptime);
}

//Processo constante
void loop()
{
  Blynk.run();
  timer.run();
}
