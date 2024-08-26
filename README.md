# DataSoaker
LoRaWAN Data soaker

Step
1. Download https://github.com/adafruit/Adafruit_nRF52_nrfutil/releases/download/0.5.3.post17/adafruit-nrfutil--0.5.3.post17-win.zip
2. Download https://github.com/r4wk/R4K-DataSoaker/releases/download/pre/data_soaker_v0.1.zip
3. Run command `adafruit-nrfutil dfu serial --package data_soaker_v0.1.zip -p <port> -b 115200` (Replace <port> with COM port of your RAK4630)
4. Set LoRa settings through your favorite terminal program paired with AT Commands https://github.com/beegee-tokyo/WisBlock-API/blob/main/AT-Commands.md. Or if you have Android (easist option) set LoRa setting via the WisBlock-Toolbox app https://play.google.com/store/apps/details?id=tk.giesecke.wisblock_toolbox&pcampaignid=web_share



Of course you can compile it yourself with VSCode and PlatformIO. https://docs.rakwireless.com/Knowledge-Hub/Learn/Board-Support-Package-Installation-in-PlatformIO/
