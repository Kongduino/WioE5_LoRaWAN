/*
  Wio E5 Test EEPROM
  This example shows how to read and write bytes from/to
  the Wio E5's EEPROM (256 bytes available), specifically on the Wio Terminal.
  The code is reusable, with modifications, on other platforms using the Wio E5.
  This requires my version of the LoRaWAN library, obviously,
  It also features a few nice tricks:
  • TRNG (specific to the SAMD51)
    - getLoRandomByte():  Get one random byte.
    - fillRandom():       Fill a buffer with random bytes.
  • hexDump:  A nice hexadecimal display utility.
  (c) 2023 Kongduino
  https://github.com/Kongduino/WioE5_LoRaWAN
*/

#include <KLoRaWan.h> // I renamed the fork to be sure to avoid any confusion with the original

void hexDump(uint8_t* buf, uint16_t len) {
  // Something similar to the Unix/Linux hexdump -C command
  // Pretty-prints the contents of a buffer, 16 bytes a row
  char alphabet[17] = "0123456789abcdef";
  uint16_t i, index;
  SerialUSB.print(F("   +------------------------------------------------+ +----------------+\n"));
  SerialUSB.print(F("   |.0 .1 .2 .3 .4 .5 .6 .7 .8 .9 .a .b .c .d .e .f | |      ASCII     |\n"));
  for (i = 0; i < len; i += 16) {
    if (i % 128 == 0) SerialUSB.print(F("   +------------------------------------------------+ +----------------+\n"));
    char s[] = "|                                                | |                |\n";
    // pre-formatted line. We will replace the spaces with text when appropriate.
    uint8_t ix = 1, iy = 52, j;
    for (j = 0; j < 16; j++) {
      if (i + j < len) {
        uint8_t c = buf[i + j];
        // fastest way to convert a byte to its 2-digit hex equivalent
        s[ix++] = alphabet[(c >> 4) & 0x0F];
        s[ix++] = alphabet[c & 0x0F];
        ix++;
        if (c > 31 && c < 128) s[iy++] = c;
        else s[iy++] = '.'; // display ASCII code 0x20-0x7F or a dot.
      }
    }
    index = i >> 4;
    // display line number then the text
    if (i < 256) Serial.write(' ');
    SerialUSB.print(index, HEX); Serial.write('.');
    SerialUSB.print(s);
  }
  SerialUSB.print(F("   +------------------------------------------------+ +----------------+\n"));
}

void setup() {
  SerialUSB.begin(115200);
  lora.init();
  for (uint8_t ix = 0; ix < 3; ix++) {
    delay(1000);
    SerialUSB.print(3 - ix);
    SerialUSB.print(", ");
  }
  delay(1000);
  SerialUSB.println("0!");
  // RNG
  lora.initRandom();
  uint8_t buf0[16], buf1[16], addr = lora.getLoRandomByte() & 0xF0, ix;
  lora.fillRandom(buf0, 16);
  hexDump(buf0, 16);
  memset(buf1, 0, 16);
  SerialUSB.printf("Writing 16 bytes to address   0x%02x", addr);
  for (ix = 0; ix < 16; ix++) {
    lora.setEEPROM(addr + ix, buf0[ix]);
    SerialUSB.write('.');
  }
  Serial.println(" done!");
  SerialUSB.printf("Reading 16 bytes from address 0x%02x", addr);
  for (ix = 0; ix < 16; ix++) {
    buf1[ix] = lora.getEEPROM(addr + ix);
    SerialUSB.write('.');
  }
  Serial.println(" done!");
  hexDump(buf1, 16);
}

void loop() {
}
