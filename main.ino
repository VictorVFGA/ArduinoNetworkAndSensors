#include <DHT.h>
#include <DHT_U.h>
#include <EtherCard.h>

static byte myip[] = {192, 168, 1, 68};
static byte gwip[] = {192, 168, 1, 254};
static byte mymac[] = {0x74, 0x69, 0x69, 0x2D, 0x30, 0x31};

byte Ethernet::buffer[500];

int SENSOR = 3;
int TEMPERATURA;
int TEMPF;
int HUMEDAD;
int TRIGGER_PIN = 4;
int ECHO_PIN = 5;
int DISTANCIA;
int DURACION;
DHT dht(SENSOR, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
 
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println("Error al acceder al controlador Ethernet");

  ether.staticSetup(myip, gwip);

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

static word homePage() {
  BufferFiller bfill = ether.tcpOffset();
  bfill.emit_p(PSTR("HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "<!DOCTYPE html>\r\n"
                    "<html>\r\n"
                    "<head>\r\n"
                    "<title>Sensor Arduino</title>\r\n"
                    "<meta charset='utf-8'>\r\n"
                    "<meta http-equiv='refresh' content='5'>\r\n"
                    "</head>\r\n"
                    "<body>\r\n"
                    "<h1>Datos de sensores del Arduino</h1>\r\n"
                    "<h2>La temperatura es de: $D °C</h2>\r\n"
                    "<h2>La temperatura es de: $D °F</h2>\r\n"
                    "<h2>La humedad es de: $D %</h2>\r\n"
                    "<h2>La distancia es de: $D cm</h2>\r\n"
                    "</body>\r\n"
                    "</html>\r\n"),
               TEMPERATURA, TEMPF, HUMEDAD, DISTANCIA);

  return bfill.position();
}

void loop() {
  if (ether.packetLoop(ether.packetReceive())) {
    TEMPERATURA = dht.readTemperature();
    HUMEDAD = dht.readHumidity();
    TEMPF = dht.readTemperature(true);

    // Realizar la medición de distancia con el sensor HC-SR04
    digitalWrite(TRIGGER_PIN, HIGH); 
    delay(1);
    digitalWrite(TRIGGER_PIN, LOW); 
    DURACION = pulseIn(ECHO_PIN, HIGH); 
    DISTANCIA = DURACION / 58; 
    Serial.println("Respuesta enviada");
    ether.httpServerReply(homePage());
    //delay(2000);
  }
}
