#include <KLoRaWan.h>

unsigned char buffer[16];

void setup(void) {
  SerialUSB.begin(115200);
  lora.init();
  lora.initP2PMode(433, SF12, BW125, 8, 8, 20);
}

void loop(void) {
  SerialUSB.print("Sending string...");
  lora.transferPacketP2PMode("Hello World!");
  SerialUSB.println(" done!");
  delay(10000);
  lora.fillRandom(buffer, 16);
  SerialUSB.print("Sending hex array...");
  lora.transferPacketP2PMode(buffer, 16);
  SerialUSB.println(" done!");
  delay(10000);
}
