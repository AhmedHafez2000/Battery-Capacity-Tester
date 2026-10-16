# Battery-Capacity-Tester

A device used to measure the capacity of Li-ion batteries with charging or discharging them with selectable discharge rate.

This is an Arduino Nano-based device, utilizing the **LGT8F328P - (Enhanced Arduino-Compatible Microcontroller)**. This microcontroller provides more accurate measurements due to its 12-bit ADC.

For more information about the LGT8F328P, see the following link:
https://github.com/AhmedHafez2000/Arduino-Nano-Clone-LGT8F328P

#### Measurement Procedure:
- The battery tester can calculate the capacity by 2 methods as follows:
1. Discharging Method: Batteries are discharged with constant current load which is set using multiturn potentiometer in range from 50mA to 1A.
2. Charging Method: Batteries are charged using TP4056 IC which is a complete constant-current/constant-voltage (CC/CV) linear charging integrated circuit.
- To select charging or discharging test **press once** on the push button.
- To start the test **hold press** the push button.
- To reset the calculated capacity **double press** the push button.


#### Key Features:
- **Constant Discharge**: Can select the discharge rate using multiturn potentiometer and it is viewed on TFT display.
- **Reverse Polarity Protection**: The device has a reverse polarity protection circuit that isolate the battery and protect it from damage, if the battery is reversed it show on the display.
- **Power Supply**: Can be powered using a Li-ion battery (support only discharge mode only). The battery will be charged when the device is powered using USB, the battery will protect the readings from getting lost.
- **Active Cooling**: Power MOSFET's heatsink is cooled by 12V fan which is connected to its connector on the PCB.

This **Battery Capacity Tester** can be fabricated at home. A printable file is attached in the PCB folder.


#### NOTES:
- All designs are made with ease of home fabrication in mind, which is why we use wider traces where possible.
- Components were chosen based on availability, so you can modify the package size while keeping the same values.
- MOSFETs must be attached to heatsink with isolating thermal sheet and screw isolator.
- When the device is powered via USB, with a Li-ion battery as a backup, disconnecting the USB power will not affect the discharging test mode, which will continue normally. However, the charging test mode will stop.



---

## DIY Sample

![](https://github.com/AhmedHafez2000/Battery-Capacity-Tester/blob/main/Photos/IMG_6.jpg?raw=true)
![](https://github.com/AhmedHafez2000/Battery-Capacity-Tester/blob/main/Photos/IMG_5.jpg?raw=true)
![](https://github.com/AhmedHafez2000/Battery-Capacity-Tester/blob/main/Photos/IMG_8.jpg?raw=true)
![](https://github.com/AhmedHafez2000/Battery-Capacity-Tester/blob/main/Photos/IMG_9.jpg?raw=true)
![](https://github.com/AhmedHafez2000/Battery-Capacity-Tester/blob/main/Photos/IMG_1.jpg?raw=true)
![](https://github.com/AhmedHafez2000/Battery-Capacity-Tester/blob/main/Photos/IMG_3.jpg?raw=true)

---

## Schematic

![Schematic](https://github.com/AhmedHafez2000/Battery-Capacity-Tester/blob/main/Schematic/Schematic_Battery_Tester.png?raw=true)


- MT3608 boost converter is used to supply a stable voltage level followed by LDOs.
- Device can be power with micro USB or USB type-C.

---

## 2D PCB
![2D PCB](https://github.com/AhmedHafez2000/Battery-Capacity-Tester/blob/main/PCB/2D-Bot.png?raw=true)

**NOTE:** The top connection are jumper wires.

---

## 3D PCB
![3D PCB](https://github.com/AhmedHafez2000/Battery-Capacity-Tester/blob/main/PCB/3D-Top.png?raw=true)
![3D PCB](https://github.com/AhmedHafez2000/Battery-Capacity-Tester/blob/main/PCB/3D-Bot.png?raw=true)