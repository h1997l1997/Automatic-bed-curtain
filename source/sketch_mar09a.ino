#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include <EEPROM.h>
//=======wifi和校时=======
const char *ssid     = "IT-IoT"; //wifi的ssid
const char *password = "s22b4e2q";//wifi的密码
float clock_time=18.41; //设置的闹钟时间，小数位表示分钟，整数位表示小时
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
float time_now=0;
//=======IO定义==========
int close1=5;
int open1=4;
int temp=0;
int flag=0;
int button1=14;
void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(close1, OUTPUT);
  pinMode(open1, OUTPUT);
  pinMode(button1, INPUT);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
  EEPROM.begin(64);
}

void button()
{
  int temp_2=digitalRead(button1);
  if (temp_2==HIGH)  temp=1;
  }
  
void close2(){
  digitalWrite(close1,HIGH);
  digitalWrite(open1,LOW);
  delay(1000);
  digitalWrite(close1,LOW);
  digitalWrite(open1,LOW);
  flag=1;
  EEPROM.write(0, flag);
  EEPROM.commit();
  Serial.println("close");
  }

void open2(){
  digitalWrite(close1,LOW);
  digitalWrite(open1,HIGH);
  delay(1000);
  digitalWrite(close1,LOW);
  digitalWrite(open1,LOW);
  flag=0;
  EEPROM.write(0, flag);
  EEPROM.commit();
  Serial.println("open");
  }

void button_move()
{
  if (temp==1)
  {
    if (flag==1)
      {
        open2();
        temp=0;
      }
    else  {
        close2();
        temp=0;
      }
    }
  }

void get_time(){
  int hour=timeClient.getHours()+8;
  int minute=timeClient.getMinutes();
  time_now=hour+minute*0.01;
  }

void clock_move()
{
  if (time_now-clock_time>=0 &&  time_now-clock_time<=1)
   { if (flag==1)
    {open2();
     Serial.println("auto_open");}}
  }
void loop() {
  flag=EEPROM.read(0);
  //if (flag!=1 || flag!=0)
  //{
  //  flag=0;
  //  }
  digitalWrite(close1,LOW);
  digitalWrite(open1,LOW);
  timeClient.update();
  button();
  button_move();
  get_time();
  clock_move();
  int b=timeClient.getMinutes();
  int a=timeClient.getHours()+8;
  Serial.println(flag);
  //delay(1000);
}
