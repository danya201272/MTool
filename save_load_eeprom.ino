
  result Save1() {
  EEPROM.begin(512); 
  delay(20);
  EEPROM.put(0, value);
  EEPROM.put(8, bitlength);
  EEPROM.put(12, protocol);
  EEPROM.put(16, pulselength);
  EEPROM.commit();
  EEPROM.end();
  return proceed;
  } 

  result Save2() {
  EEPROM.begin(512); 
  delay(20);
  EEPROM.put(20, value);
  EEPROM.put(28, bitlength);
  EEPROM.put(32, protocol);
  EEPROM.put(36, pulselength);
  EEPROM.commit();
  EEPROM.end();
  return proceed;
  } 

  result Save3() {
  EEPROM.begin(512); 
  delay(20);
  EEPROM.put(40, value);
  EEPROM.put(48, bitlength);
  EEPROM.put(52, protocol);
  EEPROM.put(56, pulselength);
  EEPROM.commit();
  EEPROM.end();
  return proceed;
  } 

  result Save4() {
  EEPROM.begin(512); 
  delay(20);
  EEPROM.put(60, value);
  EEPROM.put(68, bitlength);
  EEPROM.put(72, protocol);
  EEPROM.put(76, pulselength);
  EEPROM.commit();
  EEPROM.end();
  return proceed;
  } 

  result Save5() {
  EEPROM.begin(512); 
  delay(20);
  EEPROM.put(80, value);
  EEPROM.put(88, bitlength);
  EEPROM.put(92, protocol);
  EEPROM.put(96, pulselength);
  EEPROM.commit();
  EEPROM.end();
  return proceed;
  }

  result Save6() {
  EEPROM.begin(512); 
  delay(20);
  EEPROM.put(100, value);
  EEPROM.put(108, bitlength);
  EEPROM.put(112, protocol);
  EEPROM.put(116, pulselength);
  EEPROM.commit();
  EEPROM.end();
  return proceed;
  }

  result Save7() {
  EEPROM.begin(512); 
  delay(20);
  EEPROM.put(120, value);
  EEPROM.put(128, bitlength);
  EEPROM.put(132, protocol);
  EEPROM.put(136, pulselength);
  EEPROM.commit();
  EEPROM.end();
  return proceed;
  }

  result Save8() {
  EEPROM.begin(512); 
  delay(20);
  EEPROM.put(140, value);
  EEPROM.put(148, bitlength);
  EEPROM.put(152, protocol);
  EEPROM.put(156, pulselength);
  EEPROM.commit();
  EEPROM.end();
  return proceed;
  }

  result Save9() {
  EEPROM.begin(512); 
  delay(20);
  EEPROM.put(160, value);
  EEPROM.put(168, bitlength);
  EEPROM.put(172, protocol);
  EEPROM.put(176, pulselength);
  EEPROM.commit();
  EEPROM.end();
  return proceed;
  }


//Load

  result Load1() {
  EEPROM.begin(512);
  delay(20);
  EEPROM.get(0, value);
  EEPROM.get(8, bitlength);
  EEPROM.get(12, protocol);
  EEPROM.get(16, pulselength);
  u8g2.clearBuffer();
  u8g2.println(value);
  u8g2.println(bitlength);
  u8g2.println(protocol);
  u8g2.println(pulselength);
  return proceed;
  } 

  result Load2() {
  EEPROM.begin(512);
  delay(20);
  EEPROM.get(20, value);
  EEPROM.get(28, bitlength);
  EEPROM.get(32, protocol);
  EEPROM.get(36, pulselength);
  u8g2.clearBuffer();
  u8g2.println(value);
  u8g2.println(bitlength);
  u8g2.println(protocol);
  u8g2.println(pulselength);
  return proceed;
  } 

  result Load3() {
  EEPROM.begin(512);
  delay(20);
  EEPROM.get(40, value);
  EEPROM.get(48, bitlength);
  EEPROM.get(52, protocol);
  EEPROM.get(56, pulselength);
  u8g2.clearBuffer();
  u8g2.println(value);
  u8g2.println(bitlength);
  u8g2.println(protocol);
  u8g2.println(pulselength);
  return proceed;
  } 

  result Load4() {
  EEPROM.begin(512);
  delay(20);
  EEPROM.get(60, value);
  EEPROM.get(68, bitlength);
  EEPROM.get(72, protocol);
  EEPROM.get(76, pulselength);
  u8g2.clearBuffer();
  u8g2.println(value);
  u8g2.println(bitlength);
  u8g2.println(protocol);
  u8g2.println(pulselength);
  return proceed;
  } 

  result Load5() {
  EEPROM.begin(512);
  delay(20);
  EEPROM.get(80, value);
  EEPROM.get(88, bitlength);
  EEPROM.get(92, protocol);
  EEPROM.get(96, pulselength);
  u8g2.clearBuffer();
  u8g2.println(value);
  u8g2.println(bitlength);
  u8g2.println(protocol);
  u8g2.println(pulselength);
  return proceed;
  }

  result Load6() {
  EEPROM.begin(512);
  delay(20);
  EEPROM.get(100, value);
  EEPROM.get(108, bitlength);
  EEPROM.get(112, protocol);
  EEPROM.get(116, pulselength);
  u8g2.clearBuffer();
  u8g2.println(value);
  u8g2.println(bitlength);
  u8g2.println(protocol);
  u8g2.println(pulselength);
  return proceed;
  } 

  result Load7() {
  EEPROM.begin(512);
  delay(20);
  EEPROM.get(120, value);
  EEPROM.get(128, bitlength);
  EEPROM.get(132, protocol);
  EEPROM.get(136, pulselength);
  u8g2.clearBuffer();
  u8g2.println(value);
  u8g2.println(bitlength);
  u8g2.println(protocol);
  u8g2.println(pulselength);
  return proceed;
  } 

  result Load8() {
  EEPROM.begin(512);
  delay(20);
  EEPROM.get(140, value);
  EEPROM.get(148, bitlength);
  EEPROM.get(152, protocol);
  EEPROM.get(156, pulselength);
  u8g2.clearBuffer();
  u8g2.println(value);
  u8g2.println(bitlength);
  u8g2.println(protocol);
  u8g2.println(pulselength);
  return proceed;
  } 

  result Load9() {
  EEPROM.begin(512);
  delay(20);
  EEPROM.get(160, value);
  EEPROM.get(168, bitlength);
  EEPROM.get(172, protocol);
  EEPROM.get(176, pulselength);
  u8g2.clearBuffer();
  u8g2.println(value);
  u8g2.println(bitlength);
  u8g2.println(protocol);
  u8g2.println(pulselength);
  return proceed;
  }