#include <KLoRaWan.h>

unsigned char buffer[16];

void setup(void) {
  SerialUSB.begin(115200);
  lora.init();
  lora.initP2PMode(868.125, SF12, BW125, 8, 8, 20);
}

void loop(void) {
  short length = 0;
  short rssi, snr;
  memset(buffer, 0, 16);
  length = lora.receivePacketP2PMode(buffer, 16, &rssi, &snr, 1);
  // The original library doesn't return SNR – which is just as important as RSSI.
  if (length) {
    SerialUSB.printf("Length: %d. RSSI: %d. SNR: %d", length, rssi, snr);
    SerialUSB.print("Data:\n");
    for (unsigned char i = 0; i < length; i ++) {
      SerialUSB.printf("0x%02x ", buffer[i]);
    }
    SerialUSB.write('\n');
  }
}
