# Automatic Arduino Fan with Fan Speed Adjustment and LCD
 
# Description
A threshold temperature is set in the cold prior to the start of the program. This threshold temperature determines when the fan turns on and turns off. After that is set and the system is powered up, the temperature sensor determines the current temperature and compares it to the set threshold temperature. If the current temperature is equal to or higher than the threshold temperature, the fan will turn on at a speed of 170. The LCD screen will show the current temperature, that the fan is on, and the current fan speed. During the time that the fan is on, the 2 buttons can be used to adjust the fan speed. The top button increases fan speed by an increment of 10 while the bottom button decreases fan speed by an increment of 10. The minimum and maximum speeds for the fan set are 100 and 250 respectively. Pressing the decrement button while the fan is at the lowest speed and the increment button while the fan is at the highest speed will not do anything. Similarly, pressing the buttons when the fan is not active will also not do anything. Holding a button when the fan is on will only increment or decrement once and will not continuously increase or decrease the fan speed. When the temperature drops below the threshold temperature, the fan will turn off. The LCD will display the current temperature, the fan is off, and the current humidity. If the temperature increases to the threshold temperature again or above, the same process will start again. The only difference is that the fan speed will be set to the previously set fan speed. The default fan speed is only set at 170 when the system first starts.

# Components
- UNO R3 Controller Board
- 830 Tie-Points Breadboard
- DHT11 Temperature and Humidity Module
- Fan Blade and 3-6V Motor
- Female to Male Dupont Wires
- Buttons
- 10k Potentiometer
- Breadboard Jumper Wires
- LCD1602 Module

# Schematics

## Temperature Sensor Module
<img src="https://user-images.githubusercontent.com/81611522/185214815-aa5617b3-6c22-477f-8eb9-570f0d6445f3.png" width="500">

## LCD1602
<img src="https://user-images.githubusercontent.com/81611522/185214833-98cf13b4-10bb-4efb-98ad-6465e6dd37c3.png" width="500">


## L293D and Fan Blade and 3-6V Motor
<img src="https://user-images.githubusercontent.com/81611522/185214781-440791dc-a773-4d86-819f-7179605d1e00.png" width="500">


## General Overview
<img src="https://user-images.githubusercontent.com/81611522/185214807-6283db80-511f-4948-9261-c16456ef4906.png" width="500">

