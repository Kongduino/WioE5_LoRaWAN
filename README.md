# KLoRaWAN

A fork of the LoRaWAN library for the Wio-E5, specifically targeting the Wio Terminal+LoRaWAN Chassis. It adds a few commands and facilities:

* EEPROM: save/load bytes from the Wio E5's EEPROM.
  A `Test_EEPROM` sketch has been added to the examples.
* SNR: The `receivePacketP2PMode()` function now returns SNR along with RSSI.
  The `p2p_rx` / `p2p_tx` sketches use this facility.
* TRNG
  TRNG is used in the `Test_EEPROM` and `p2p_rx` / `p2p_tx` sketches.

I have left the `ABP` and `OTAA` sketches alone, as I am dealing only with LoRa here.

This fork will stay in place until SeeedStudio merges it back to the original – I am in contact with them and they have been very responsive.

I have also reformatted the library so it it confirms to the current standard (src folder, keywords.txt, etc).