char* byteArrToStr(byte* arr, unsigned int len)
{
  char outStr[len * 2];
  for (unsigned int i = 0; i < len; i++)
  {
    byte n1 = (arr[i] >> 4) & 0x0F;
    byte n2 = (arr[i] >> 0) & 0x0F;
    outStr[i * 2 + 0] = n1 < 0xA ? '0' + n1 : 'A' + n1 - 0xA;
    outStr[i * 2 + 1] = n2 < 0xA ? '0' + n2 : 'A' + n2 - 0xA;
  }
  outStr[len * 2] = '\0';

  return outStr;
}

void generateWhoAmi()
{


}

void composeNodeMCUInfo()
{
  

}

void composeWEMOSD1MiniInfo()
{
  
}


/*

  class ESPMaster {
  private:
    uint8_t _ss_pin;
    void _pulseSS() {
      digitalWrite(_ss_pin, HIGH);
      delayMicroseconds(5);
      digitalWrite(_ss_pin, LOW);
    }
  public:
    ESPMaster(uint8_t pin): _ss_pin(pin) {}
    void begin() {
      pinMode(_ss_pin, OUTPUT);
      _pulseSS();
    }

    uint32_t readStatus() {
      _pulseSS();
      SPI.transfer(0x04);
      uint32_t status = (SPI.transfer(0) | ((uint32_t)(SPI.transfer(0)) << 8) | ((uint32_t)(SPI.transfer(0)) << 16) | ((uint32_t)(SPI.transfer(0)) << 24));
      _pulseSS();
      return status;
    }

    void writeStatus(uint32_t status) {
      _pulseSS();
      SPI.transfer(0x01);
      SPI.transfer(status & 0xFF);
      SPI.transfer((status >> 8) & 0xFF);
      SPI.transfer((status >> 16) & 0xFF);
      SPI.transfer((status >> 24) & 0xFF);
      _pulseSS();
    }

    void readData(uint8_t * data) {
      _pulseSS();
      SPI.transfer(0x03);
      SPI.transfer(0x00);
      for (uint8_t i = 0; i < 32; i++) {
        data[i] = SPI.transfer(0);
      }
      _pulseSS();
    }

    void writeData(uint8_t * data, size_t len) {
      uint8_t i =  0;
      _pulseSS();
      SPI.transfer(0x02);
      SPI.transfer(0x00);
      while (len-- && i < 32) {
        SPI.transfer(data[i++]);
      }
      while (i++ < 32) {
        SPI.transfer(0);
      }
      _pulseSS();
    }

    String readData() {
      char data[33];
      data[32] = 0;
      readData((uint8_t *)data);
      return String(data);
    }

    void writeData(const char * data) {
      writeData((uint8_t *)data, strlen(data));
    }
  };
*/