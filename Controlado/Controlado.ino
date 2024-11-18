#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define echoPin 14
#define trigPin 12

const char* ssid = "Xiaomi 11T";
const char* password = "santotomas";
const char* mqtt_server = "test.mosquitto.org";  // Este es el address en mqtt dash
const char* keyDevice = "";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

long duration;
int distance;
// Motor dirección
int MB2 = 2;
int MB1 = 4;
int MA2 = 0;
int MA1 = 5;
// Led
int led1 = 15;
int led2 = 16;
// Buzzer
int buzzer = 13;

void setup_wifi() {
    delay(10);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("OK");
}

void callback(char* topic, byte* payload, unsigned int length) {
    String topico = topic;
    if (topico == "st/01") {
        if ((char)payload[0] == '1') {  // 1 para prender
            digitalWrite(MA1, HIGH);                 
            digitalWrite(MA2, HIGH);
            digitalWrite(MB1, HIGH);                              
            digitalWrite(MB2, LOW);
            Serial.println("Avanzar");
        } else if ((char)payload[0] == '0') {  // 0 para apagar
            digitalWrite(MA1, LOW);
            digitalWrite(MA2, LOW);
            digitalWrite(MB1, LOW);
            digitalWrite(MB2, LOW);
            Serial.println("Stop");
        }
    } else if (topico == "st/02") {
        if ((char)payload[0] == '1') {  // 1 para prender
            digitalWrite(MA1, HIGH);
            digitalWrite(MA2, LOW);
            digitalWrite(MB1, HIGH);
            digitalWrite(MB2, HIGH);
            Serial.println("Retroceder");
        } else if ((char)payload[0] == '0') {  // 0 para apagar
            digitalWrite(MA1, LOW);
            digitalWrite(MA2, LOW);
            digitalWrite(MB1, LOW);
            digitalWrite(MB2, LOW);
            Serial.println("Stop");
        }
    } else if (topico == "st/03") {
        if ((char)payload[0] == '1') {  // 1 para prender
            digitalWrite(MA1, HIGH);
            digitalWrite(MA2, LOW);
            digitalWrite(MB1, HIGH);
            digitalWrite(MB2, LOW);
            Serial.println("Giro Izq");
        } else if ((char)payload[0] == '0') {  // 0 para apagar
            digitalWrite(MA1, LOW);
            digitalWrite(MA2, LOW);
            digitalWrite(MB1, LOW);
            digitalWrite(MB2, LOW);
            Serial.println("Stop");
        }
    } else if (topico == "st/04") {
        if ((char)payload[0] == '1') {  // 1 para prender
            digitalWrite(MA1, HIGH);
            digitalWrite(MA2, HIGH);
            digitalWrite(MB1, HIGH);
            digitalWrite(MB2, HIGH);
            Serial.println("Giro Derecha");
        } else if ((char)payload[0] == '0') {  // 0 para apagar
            digitalWrite(MA1, LOW);
            digitalWrite(MA2, LOW);
            digitalWrite(MB1, LOW);
            digitalWrite(MB2, LOW);
            Serial.println("Stop");
        }
    }
}

void reconnect() {
    if (!client.connected()) {
        if (client.connect(keyDevice, "", "")) {  // Servidor broker es el usuario y prueba12 la contraseña en mqtt dash
            Serial.println("connected");
            client.subscribe("st/#");  // Topico al momento de crear el boton
        } else {
            delay(5000);
        }
    }
}

void setup() {
    pinMode(MB2, OUTPUT);
    pinMode(MB1, OUTPUT);
    pinMode(MA2, OUTPUT);
    pinMode(MA1, OUTPUT);
    Serial.begin(9600);
    Serial.println("iniciando");
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
