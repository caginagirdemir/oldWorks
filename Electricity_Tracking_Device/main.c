#include "ESP8266WiFi.h"
#include "EEPROM.h"
#include "ThingSpeak.h"
char ssid[20];
char password[20];
char kaydedilendeger;
int n;
int sensorTA12 = A0;
int a = 0;
boolean k;
bool bir =true;
static inline unsigned get_ccount(void);
String ApiKey = "YSN5S0VR294T3H13";
String path = "/update?key=" + ApiKey + "&field1=";
const char* host = "api.thingspeak.com";
int port = 80;
void fonk()
{
  for (int i = 0; i <60 ; ++i){EEPROM.write(i, 0);}
  EEPROM.commit();
  while(1)
  {}
}
void setup() {
//////////////// Definations
EEPROM.begin(512);
pinMode(sensorTA12, INPUT);
Serial.begin(115200);
pinMode(14, OUTPUT);  // Eprom kayıt D5
pinMode(13, OUTPUT); //USB Bağlantı D7
pinMode(12, OUTPUT); // Wifi Bağlantı ledi D6
pinMode(0, OUTPUT); // Eprom kontrol D3
pinMode(15, OUTPUT); // röle sürme
pinMode(5, OUTPUT);  //röle led acik D1
pinMode(16, OUTPUT);  //röle led kapali D0
WiFi.mode(WIFI_STA);
  
//////////////// Initilazitaion
if(epromkotnrol())
{digitalWrite(0, HIGH);
  goto go;}
  
//////////////// Usb Check
Serial.println("OK2");
while(1)[if(Serial.find("komut1")) break;}
Serial.println("OK3");
digitalWrite(13, HIGH); 
delay(100);

//////////////// Wifi scan
Serial.println("scan start");
n = WiFi.scanNetworks();
Serial.println(n);
Serial.println("scan done");
if (n == 0)
Serial.println("no networks found");
else{
    Serial.print(n);
    Serial.println(" networks found");
    Serial.println("scan done 1");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(i + 1);
      Serial.print(": [");
      Serial.print(WiFi.SSID(i));
      Serial.print(" ](");
      Serial.print(WiFi.BSSIDstr(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);   } }
Serial.println("wifiscantamam");


//////////////// Wait WifiInfo
while(1)
{if(Serial.find("ssidsend")) break;}
degeroku().toCharArray(ssid, 50) ;
Serial.println("ssidOK");
while(1)
{if(Serial.find("passsend")) break;}
degeroku().toCharArray(password, 50) ;
Serial.println("passOK");

//////////////// Connect to Network
go:
Serial.print(ssid);
Serial.print(password);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  digitalWrite(12, HIGH); 
  delay(500);
  digitalWrite(12, LOW); }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(12, HIGH);
  if(!epromkotnrol())
  {EEPROM.commit();
char degisken1[] = "kurulu";
for (int i = 0; i < 7 ; ++i)
{EEPROM.write(i, degisken1[i]);}
for (int i = 10; i < 30 ; ++i)
{EEPROM.write(i, ssid[i-10]);}
for (int i = 30; i < 50 ; ++i)
{EEPROM.write(i, password[i-30]);}
EEPROM.commit();
  digitalWrite(14, HIGH);}}
void loop() {thingspeak();}
bool epromkotnrol()
{
    String deger;
    String ssidstr;
    String passstr;
    for (int i = 0; i < 10; ++i)
    {deger += char(EEPROM.read(i)); }
    if(deger =="kurulu")
    { for (int i = 10; i < 29; ++i) {
      ssidstr += char(EEPROM.read(i)); }
    for (int i = 30; i < 50; ++i)
    { passstr += char(EEPROM.read(i)); }
    ssidstr.trim();
    passstr.trim();
    ssidstr.toCharArray(ssid, 20) ;
    passstr.toCharArray(password, 20);
    return true;
    } else { return false;}}

void thingspeak()
{Serial.print("connecting to ");
    Serial.println(host);
    WiFiClient client;
    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;}
    ThingSpeak.begin(client);
    int tick1 = get_ccount(); 
    git2:
    k = ThingSpeak.readIntField(202791, 2, "7LBDY3G91VEV0F91"); 
        Serial.println(k);
    if(k)
    {
      digitalWrite(15,LOW);
      digitalWrite(5,HIGH);
      digitalWrite (16,LOW);
    } if(!k) {
      digitalWrite(15,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(16,HIGH);  }
    int tick2 = get_ccount(); 
    int tickdiff = tick2 - tick1;
    if(tickdiff <= 1000000000)
    { goto git2; }
    float sensor = sensoroku();
    ThingSpeak.writeField(202791, 1, sensor, "YSN5S0VR294T3H13"); }
float sensoroku() {
float nVPP;   // Voltage measured across resistor
float deger; // Peak Current Measured Through Resistor
   nVPP = getVPP();
   deger = (nVPP/200.0) * 1000.0 * 0.707;
   deger = deger;
   return deger; }
float getVPP() {
  float result;
  int readValue;
  int maxValue = 0;         
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000)
   {
       readValue = analogRead(sensorTA12);
       if (readValue > maxValue) 
       {           maxValue = readValue; } }
   result = (maxValue * 5.0)/1024.0;
   return result; }
String degeroku()
{
  String okunandeger = "";
  do{
  while (Serial.available())  {
      char c = Serial.read(); 
      okunandeger += c;  }
  if(okunandeger.indexOf(";") != -1) break;
  }while(1);
  okunandeger.remove(okunandeger.length()-1);
  okunandeger.trim();
  return okunandeger;
}
/////////////////////////timer fonk.
static inline unsigned get_ccount(void)
{
        unsigned r;
        asm volatile ("rsr %0, ccount" : "=r"(r));
        return r;
}
