#include <ESPAsyncWebServer.h>

#include <WiFi.h>

#define PIN_A_MOTOR1 13
#define PIN_B_MOTOR1 4
#define PIN_A_MOTOR2 5
#define PIN_B_MOTOR2 24

const char *ssid = "GHOST";
const char *password = "qwerty123";

AsyncWebServer server(80);

float velocidad_Izquierda; 
float velocidad_Derecha; 

void setup() 
{
  Serial.begin(9600);

  pinMode(PIN_A_MOTOR1, OUTPUT);
  pinMode(PIN_B_MOTOR1, OUTPUT);
  pinMode(PIN_A_MOTOR2, OUTPUT);
  pinMode(PIN_B_MOTOR2, OUTPUT);
  
  WiFi.softAP(ssid, password); //ESP32 configurada como punto de acceso 
 
  Serial.println("Punto de acceso iniciado");
  Serial.println("IP del punto de accceso: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET,[](AsyncWebServerRequest *request)
  {
    request->send(200,"text/plain",
    "Servidor ESP32 encendido");
  });

  server.on("/mover1",HTTP_GET,[](AsyncWebServerRequest *request)
  {
    String velocidad_str = request->getParam("velocity")->value();
    float velocidad = velocidad_str.toInt();

    if(velocidad > 0)
    {
      digitalWrite(PIN_A_MOTOR1, HIGH);
      digitalWrite(PIN_B_MOTOR1, LOW);
      request->send(200, "text/plain", "OK mover1 avanza");      
    }

    if(velocidad < 0)
    {
      digitalWrite(PIN_A_MOTOR1, LOW);
      digitalWrite(PIN_B_MOTOR1, HIGH);
      request->send(200, "text/plain", "OK mover1 retrocede"); 
    }

    analogWrite(abs(velocidad)*255, 22);
  });

 server.on("/mover2",HTTP_GET,[](AsyncWebServerRequest *request)
  {
    String velocidad_str = request->getParam("velocity")->value();
    float velocidad = velocidad_str.toInt();

    if(velocidad > 0)
    {
      digitalWrite(PIN_A_MOTOR1, HIGH);
      digitalWrite(PIN_B_MOTOR1, LOW);
      request->send(200, "text/plain", "OK mover2 avanza");      
    }

    if(velocidad < 0)
    {
      digitalWrite(PIN_A_MOTOR1, LOW);
      digitalWrite(PIN_B_MOTOR1, HIGH);
      request->send(200, "text/plain", "OK mover2 retrocede"); 
    } 

    analogWrite(abs(velocidad)*255, 23);
  });

  server.on("/stop1",HTTP_GET,[](AsyncWebServerRequest *request)
  {
    String velocidad_str = request->getParam("velocity")->value();
    float velocidad = velocidad_str.toInt();

    if(velocidad == 0)
    {
      digitalWrite(PIN_A_MOTOR1, LOW);
      digitalWrite(PIN_B_MOTOR1, LOW);
      request->send(200, "text/plain", "OK stop1 detiene");      
    }
  });

   server.on("/stop2",HTTP_GET,[](AsyncWebServerRequest *request) 
  {
    String velocidad_str = request->getParam("velocity")->value();
    float velocidad =  velocidad_str.toInt();

    if(velocidad == 0)
    {
      digitalWrite(PIN_A_MOTOR2, LOW);
      digitalWrite(PIN_B_MOTOR2, LOW);
      (200, "text/plain", "OK stop2 detiene");      
    }    
  });

  

  server.begin();
}

void loop() 
{

}
