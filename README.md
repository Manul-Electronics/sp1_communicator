# P1 Wireless Interface (P1WI)
Smart Meter serial to wireless interface (Wi-Fi).

## Configuration
1. Plug a USB-C cable in the USB-C port of the P1WI.
2. Connect the other end of the cable to your PC.
3. Start the **P1WI Utility** program and click on **Start the configuration** button. This action will start the configuration wizard.
4. When prompted to do it, select the Wi-Fi network on which the P1WI should connect. If your Wi-Fi network does not pop in the list, please verify that it operates at 2.4GHz as 5.0GHz network are not supported by the ESP32 series.
5. Once the Wi-Fi network is selected, enter you Wi-Fi password into the textbox. By default, the text is obscucated, click on **Reveal passphrase** to make it appear.
6. Click on **Next**. The P1WI should now try to connect to your network. If connection is successfuly established, the program will allow you to go to the next step. In case of failure at this step, please double check your Wi-Fi password and check that P1WI is close enough of your Wi-Fi router (the network symbol should be as full as possible).
7. The configuration is now completed and the **P1WI Utility** program should display the following message : *Configuration completed successfuly. You can now disconnect the P1WI from your computer.*
8. After you unplugged it from your computer, take the RJ11 cable and connect it to the P1 Port of your Smart Energy Meter. To do this, lift up the green/yellow cover of your Smart Energy Meter and plug it in.
9. Connect the other end of the cable to you P1WI. A red light should have been lightning up, indicating that the module is powered by the Smart Energy Meter, once connected onto your Wi-Fi, a green/yellow LED should also have been lightning up. If the connection failed, a second red LED will light up.
10. If everything went well, you can now use your P1WI.

## How to use it?
