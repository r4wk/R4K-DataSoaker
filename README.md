# DataSoaker
LoRaWAN Data soaker

Step
1. Download https://github.com/adafruit/Adafruit_nRF52_nrfutil/releases/download/0.5.3.post17/adafruit-nrfutil--0.5.3.post17-win.zip
2. Download https://github.com/r4wk/R4K-DataSoaker/releases/download/pre/data_soaker_v0.2.zip
3. Run command `adafruit-nrfutil dfu serial --package data_soaker_v0.2.zip -p <port> -b 115200` (Replace \<port> with COM port of your RAK4630)
4. Set LoRa settings through your favorite terminal program paired with AT Commands https://github.com/rakstars/WisBlock-RAK4631-Helium-Mapper/wiki/Make-a-Helium-Mapper-with-the-WisBlock#over-serial.
  - If you have an Android (easist option) set LoRa setting via the WisBlock-Toolbox app https://github.com/rakstars/WisBlock-RAK4631-Helium-Mapper/wiki/Make-a-Helium-Mapper-with-the-WisBlock#using-the-wisblock-toolbox-lpwan-setup-module
  - If you use iOS then you can use this app to run AT commands over BT https://github.com/rakstars/WisBlock-RAK4631-Helium-Mapper/wiki/Make-a-Helium-Mapper-with-the-WisBlock#using-the-nrf-toolbox-uart-module

Of course you can compile it yourself with VSCode and PlatformIO. https://docs.rakwireless.com/Knowledge-Hub/Learn/Board-Support-Package-Installation-in-PlatformIO/
  - If you are compiling yourself and you don't want to use AT Commands or one of the Bluetooth options. You can now add LoRa settings in the app.h file.
