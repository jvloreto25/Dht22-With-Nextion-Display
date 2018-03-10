#include "DHT.h"
#include "Nextion.h"
#include <EEPROM.h>
#define DHTPIN 2
#define DHTTYPE DHT22

int humidity1,temperature1,moist,dry,cold,hot,count,alarm;
int buzzer      = 3;
int memorymoist = 0;
int memorydry   = 1;
int memorycold  = 2;
int memoryhot   = 3;
int memoryalarm = 4;
DHT dht(DHTPIN, DHTTYPE);

void n0p0PopCallback(void *ptr);
void n1p0PopCallback(void *ptr);

void n0p1PopCallback(void *ptr);
void n1p1PopCallback(void *ptr);
void n2p1PopCallback(void *ptr);

void n0p2PopCallback(void *ptr);
void n1p2PopCallback(void *ptr);

void n0p3PopCallback(void *ptr);
void n1p3PopCallback(void *ptr);

void t0p0PopCallback(void *ptr);
void t1p0PopCallback(void *ptr);
void t2p0PopCallback(void *ptr);
void t3p0PopCallback(void *ptr);

void t0p1PopCallback(void *ptr);
void t5p1PopCallback(void *ptr);

void b3p1PopCallback(void *ptr);

void b0p2PopCallback(void *ptr);
void b1p2PopCallback(void *ptr);
void b2p2PopCallback(void *ptr);
void b3p2PopCallback(void *ptr);
void b4p2PopCallback(void *ptr);

NexNumber n0p0 = NexNumber(0, 9,  "n0p0");
NexNumber n1p0 = NexNumber(0, 11, "n1p0");

NexNumber n0p1 = NexNumber(1, 9,  "n0p1");
NexNumber n1p1 = NexNumber(1, 10, "n1p1");
NexNumber n2p1 = NexNumber(1, 12, "n2p1");

NexNumber n0p2 = NexNumber(2, 4,  "n0p2");
NexNumber n1p2 = NexNumber(2, 5,  "n1p2");

NexNumber n0p3 = NexNumber(3, 4,  "n0p3");
NexNumber n1p3 = NexNumber(3, 5,  "n1p3");

NexText t0p0   = NexText(0, 15, "t10p0");
NexText t1p0   = NexText(0, 2,  "t1p0");
NexText t2p0   = NexText(0, 4,  "t3p0");
NexText t3p0   = NexText(0, 16, "t11p0");

NexText t0p1   = NexText(1, 6, "t4p1");
NexText t5p1   = NexText(1, 7, "t5p1");

NexButton b3p1 = NexButton(1, 16, "b3p1");

NexButton b0p2 = NexButton(2, 6, "b0p2");
NexButton b1p2 = NexButton(2, 7, "b1p2");
NexButton b2p2 = NexButton(2, 8, "b2p2");
NexButton b3p2 = NexButton(2, 9, "b3p2");
NexButton b4p2 = NexButton(2, 10,"b4p2");

NexButton b0p3 = NexButton(3, 6, "b0p3");
NexButton b1p3 = NexButton(3, 7, "b1p3");
NexButton b2p3 = NexButton(3, 8, "b2p3");
NexButton b3p3 = NexButton(3, 9, "b3p3");
NexButton b4p3 = NexButton(3, 10,"b4p3");

char buffer[100] = {0};
NexTouch *nex_listen_list[] = 
{
    &n0p0,
    &n1p0,
    
    &n0p1,
    &n1p1,
    &n2p1,
    
    &n0p2,
    &n1p2,

    &n0p3,
    &n1p3,

    &t0p0,
    &t1p0,
    &t2p0,
    &t3p0,
    
    &t0p1,
    &t5p1,

    &b3p1,
    
    &b0p2,
    &b1p2,
    &b2p2,
    &b3p2,
    &b4p2,

    &b0p3,
    &b1p3,
    &b2p3,
    &b3p3,
    &b4p3,
    NULL
};

void n0p0PopCallback(void *ptr)
{
    dbSerialPrintln("n0p0PopCallback");
}
void n1p0PopCallback(void *ptr)
{
    dbSerialPrintln("n1p0PopCallback");
}

void n0p1PopCallback(void *ptr)
{
    dbSerialPrintln("n0p1PopCallback");
}
void n1p1PopCallback(void *ptr)
{
    dbSerialPrintln("n1p1PopCallback");
}
void n2p1PopCallback(void *ptr)
{
    dbSerialPrintln("n2p1PopCallback");
}

void n0p2PopCallback(void *ptr)
{
    dbSerialPrintln("n0p2PopCallback");
}
void n1p2PopCallback(void *ptr)
{
    dbSerialPrintln("n1p2PopCallback");
}

void n0p3PopCallback(void *ptr)
{
    dbSerialPrintln("n0p3PopCallback");
}
void n1p3PopCallback(void *ptr)
{
    dbSerialPrintln("n1p3PopCallback");
}

void t0p0PopCallback(void *ptr)
{
    dbSerialPrintln("t0p0PopCallback");
}
void t1p0PopCallback(void *ptr)
{
    dbSerialPrintln("t1p0PopCallback");
}
void t2p0PopCallback(void *ptr)
{
    dbSerialPrintln("t2p0PopCallback");
}
void t3p0PopCallback(void *ptr)
{
    dbSerialPrintln("t3p0PopCallback");
}

void t0p1PopCallback(void *ptr)
{
    dbSerialPrintln("t0p1PopCallback");
}
void t5p1PopCallback(void *ptr)
{
    dbSerialPrintln("t5p1PopCallback");
}

void b3p1PopCallback(void *ptr)
{
    uint32_t number;
    dbSerialPrintln("b3p1PopCallback");
    n2p1.getValue(&number);
    number += 1;
    alarm = number;
    EEPROM.write(memoryalarm, alarm);
}

void b0p2PopCallback(void *ptr)
{
    uint32_t numbermoist;
    dbSerialPrintln("b0p2PopCallback");
    n0p2.getValue(&numbermoist);
    numbermoist += 1;
    moist = numbermoist;
    EEPROM.write(memorymoist, moist);
}
void b1p2PopCallback(void *ptr)
{
    uint32_t numbermoist;
    dbSerialPrintln("b1p2PopCallback");
    n0p2.getValue(&numbermoist);
    numbermoist -= 1;
    moist = numbermoist;
    EEPROM.write(memorymoist, moist);
}
void b2p2PopCallback(void *ptr)
{
    uint32_t numberdry;
    dbSerialPrintln("b2p2PopCallback");
    n1p2.getValue(&numberdry);
    numberdry -= 1;
    dry = numberdry;
    EEPROM.write(memorydry, dry);
}
void b3p2PopCallback(void *ptr)
{
    uint32_t numberdry;
    dbSerialPrintln("b3p2PopCallback");
    n1p2.getValue(&numberdry);
    numberdry += 1;
    dry = numberdry;
    EEPROM.write(memorydry, dry);
}
void b4p2PopCallback(void *ptr)
{
    dbSerialPrintln("b4p2PopCallback");
    dry = 0;
    moist = 0;
    EEPROM.write(memorymoist, moist);
    EEPROM.write(memorydry, dry);
}

void b0p3PopCallback(void *ptr)
{
    uint32_t numbercold;
    dbSerialPrintln("b0p3PopCallback");
    n0p3.getValue(&numbercold);
    numbercold += 1;
    cold = numbercold;
    EEPROM.write(memorycold, cold);
}
void b1p3PopCallback(void *ptr)
{
    uint32_t numbercold;
    dbSerialPrintln("b1p3PopCallback");
    n0p3.getValue(&numbercold);
    numbercold -= 1;
    cold = numbercold;
    EEPROM.write(memorycold, cold);
}
void b2p3PopCallback(void *ptr)
{
    uint32_t numberhot;
    dbSerialPrintln("b2p3PopCallback");
    n1p3.getValue(&numberhot);
    numberhot -= 1;
    hot = numberhot;
    EEPROM.write(memoryhot, hot);
}
void b3p3PopCallback(void *ptr)
{
    uint32_t numberhot;
    dbSerialPrintln("b3p3PopCallback");
    n1p3.getValue(&numberhot);
    numberhot += 1;
    hot = numberhot;
    EEPROM.write(memoryhot, hot);
}
void b4p3PopCallback(void *ptr)
{
    dbSerialPrintln("b4p3PopCallback");
    cold = 0;
    hot = 0;
    EEPROM.write(memorycold, cold);
    EEPROM.write(memoryhot, hot);
}

void setup() 
{
  nexInit();
  pinMode(buzzer, OUTPUT);
  
  n0p0.attachPop(n0p0PopCallback);
  n1p0.attachPop(n1p0PopCallback);

  n0p1.attachPop(n0p1PopCallback);
  n1p1.attachPop(n1p1PopCallback);
  n2p1.attachPop(n2p1PopCallback);

  n0p2.attachPop(n0p2PopCallback);
  n1p2.attachPop(n1p2PopCallback);

  n0p3.attachPop(n0p3PopCallback);
  n1p3.attachPop(n1p3PopCallback);

  t0p0.attachPop(t0p0PopCallback);
  t1p0.attachPop(t1p0PopCallback);
  t2p0.attachPop(t2p0PopCallback);
  t3p0.attachPop(t3p0PopCallback);

  t0p1.attachPop(t0p1PopCallback);
  t5p1.attachPop(t5p1PopCallback);

  b3p1.attachPop(b3p1PopCallback);
  
  b0p2.attachPop(b0p2PopCallback);
  b1p2.attachPop(b1p2PopCallback);
  b2p2.attachPop(b2p2PopCallback);
  b3p2.attachPop(b3p2PopCallback);
  b4p2.attachPop(b4p2PopCallback);

  b0p3.attachPop(b0p3PopCallback);
  b1p3.attachPop(b1p3PopCallback);
  b2p3.attachPop(b2p3PopCallback);
  b3p3.attachPop(b3p3PopCallback);
  b4p3.attachPop(b4p3PopCallback);

  Serial.begin(115200);
  dht.begin();
}

void loop() 
{
  for(count = 0; count <= 10; count++)
  {
    if(count == 0)
    {
      sensor();
      nexLoop(nex_listen_list);
    }
    if(count >= 0)
    {
      n2p1.setValue(alarm);
      n0p2.setValue(moist);
      n1p2.setValue(dry);
      n0p3.setValue(cold);
      n1p3.setValue(hot);

      if(alarm == 0)
      {
        t5p1.setText("Off");
        t3p0.setText("Off");
      }
      if(alarm == 1)
      {
        t5p1.setText("On");
        t3p0.setText("On");
      }
      if(alarm >=2)
      {
        alarm = 0;
      }
      nexLoop(nex_listen_list);
    }
    delay(100);
    nexLoop(nex_listen_list);
  }
  nexLoop(nex_listen_list);
}

void sensor()
{
  
  moist = EEPROM.read(memorymoist);
  dry   = EEPROM.read(memorydry);
  cold  = EEPROM.read(memorycold);
  hot   = EEPROM.read(memoryhot);
  alarm = EEPROM.read(memoryalarm);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) 
  {
    t0p0.setText("Error");
    t0p1.setText("Error");
    
    t1p0.setText("Error");
    t2p0.setText("Error");

    if(alarm == 0)
    {
      digitalWrite(buzzer,1);
    }
    if(alarm == 1)
    {
      digitalWrite(buzzer,0);
    }
    
    n0p0.setValue(0);
    n1p0.setValue(0);
  
    n0p1.setValue(0);
    n1p1.setValue(0);
    return;
  }
  if (!isnan(h) || !isnan(t)) 
  {
    t0p0.setText("Connected");
    t0p1.setText("Connected");
  }
    
  float hic = dht.computeHeatIndex(t, h, false);
  
  humidity1 = h;
  temperature1 = t;
    
  n0p0.setValue(humidity1);
  n1p0.setValue(temperature1);
  
  n0p1.setValue(humidity1);
  n1p1.setValue(temperature1);

  if(humidity1 <= dry && humidity1 <= moist)
  {
    t1p0.setText("Dry");
    if(alarm == 0)
    {
      digitalWrite(buzzer,1);
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+639303397979\"\r"); // Replace x with mobile number
      delay(1000);
      mySerial.println("E DI WOW");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
    }
    if(alarm == 1)
    {
      digitalWrite(buzzer,0);
    }
  }
  if(humidity1 >= moist && humidity1 >= dry)
  {
    t1p0.setText("Moist");
    if(alarm == 0)
    {
      digitalWrite(buzzer,1);
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+639303397979\"\r"); // Replace x with mobile number
      delay(1000);
      mySerial.println("E DI WOW");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);

    }
    if(alarm == 1)
    {
      digitalWrite(buzzer,0);
    }
  }
  if(humidity1 >= dry && humidity1 <= moist)
  {
    t1p0.setText("Normal");
    digitalWrite(buzzer,1);
  }

  if(temperature1 <= cold && temperature1 <= hot)
  {
    t2p0.setText("Cold");
    if(alarm == 0)
    {
      digitalWrite(buzzer,1);
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+639303397979\"\r"); // Replace x with mobile number
      delay(1000);
      mySerial.println("E DI WOW");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
    }
    if(alarm == 1)
    {
      digitalWrite(buzzer,0);
    }
  }
  if(temperature1 >= hot && temperature1 >= cold)
  {
    t2p0.setText("Hot");
    if(alarm == 0)
    {
      digitalWrite(buzzer,1);
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+639303397979\"\r"); // Replace x with mobile number
      delay(1000);
      mySerial.println("E DI WOW");// The SMS text you want to send
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
    }
    if(alarm == 1)
    {
      digitalWrite(buzzer,0);
    }
  }
  if(temperature1 >= cold && temperature1 <= hot)
  {
    t2p0.setText("Normal");
    digitalWrite(buzzer,1);
  }
  
}
