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
