#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x9A, 0x55 }; //Alarma1
IPAddress serverIpEnvio(169,254,43,20);  
IPAddress ip(169, 254, 43, 10);
IPAddress myDns(169, 254, 43, 1);
IPAddress gateway(169, 254, 43, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetClient clientEnvio;
EthernetServer server(80);

const int buttonPin = 2;
const int ledPin =  7;
const int pushactive = 3;
int buttonState = 0;
int presionado = 0;
int estaEncendido = 0;
boolean lineaActualBlanco = true;
String cadena = "";

void setup() {
    Ethernet.begin(mac, ip, myDns, gateway, subnet);  
    server.begin();
    Serial.begin(9600); 
    delay(1000); 
    Serial.println("Inicio"); 
    pinMode(buttonPin, INPUT);
    pinMode(pushactive,OUTPUT); 
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
    digitalWrite(pushactive,HIGH);
            
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && presionado == 0) { 
        digitalWrite(ledPin, LOW);        
        Serial.println("Prender alarma");
        enviarCliente("1");
        estaEncendido = 1;
        presionado = 1;
        delay(200);             
  } else if (buttonState == LOW && presionado == 1) {       
        digitalWrite(ledPin, HIGH);
        Serial.println("Apagar alarma");
        enviarCliente("0");
        estaEncendido = 0;
        presionado = 0;
        delay(200); 
  }

  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        cadena += c;
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close"); 
          client.println(); 
          // Serial.println(cadena);
          cadena = cadena.substring(12,13);
          if (cadena == "1") {
              digitalWrite(ledPin, LOW);
              Serial.println("Prender alarma: Remoto");
              estaEncendido = 1;
          }
          else if (cadena == "0"){
            digitalWrite(ledPin, HIGH);
            Serial.println("Apagar alarma: Remoto");
            estaEncendido = 0;
          }
          cadena = "";        
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
  } 
}

void enviarCliente(String valor)
{
  clientEnvio.connect(serverIpEnvio, 80);
  clientEnvio.print("GET /AlarmaTec/WebService.asmx/RecibeRemoto?");
  clientEnvio.print("numIP=");
  clientEnvio.print(Ethernet.localIP());
  clientEnvio.print("&valor=");
  clientEnvio.print(valor);
  clientEnvio.println(" HTTP/1.1");
  clientEnvio.println("Host: 169.254.43.20");
  clientEnvio.println(); 
  delay(1);
  clientEnvio.stop(); 
}


