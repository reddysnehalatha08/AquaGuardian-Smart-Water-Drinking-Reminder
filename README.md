# 💧 AquaGuardian – Smart Water Drinking Reminder System

AquaGuardian is an embedded-based **Smart Water Drinking Reminder System** developed using the **LPC2148 ARM7 microcontroller**. The system helps users maintain regular water intake by providing timely reminders and tracking the number of glasses consumed throughout the day.

##  Project Overview

AquaGuardian displays the current date and time using an RTC and provides periodic reminders to drink water. Whenever a reminder is displayed, the user can press a push button to indicate that they have consumed water.

The system keeps track of the number of glasses consumed and displays the remaining target for the day. LEDs and a buzzer are used to provide additional indications and alerts.

##  Objectives

* Display real-time date and time on a 16×2 LCD.
* Provide periodic reminders to drink water.
* Record water intake using a push button.
* Track the number of glasses consumed.
* Display the remaining daily water target.
* Provide LED indications for reminder, missed reminder, and successful intake.
* Generate buzzer alerts.
* Reset the daily water intake at midnight.
* Allow configuration through a matrix keypad.

##  Hardware Requirements

* LPC2148 ARM7 Microcontroller
* 16×2 LCD
* RTC
* 4×4 Matrix Keypad
* Push Button / Switch
* LEDs
* Buzzer
* USB-to-UART Converter / DB9
* Connecting wires and power supply

##  Software & Tools

* Embedded C
* Keil µVision
* ARM7 LPC2148
* UART
* GPIO
* RTC
* LCD
* Matrix Keypad
* Interrupts

##  Working Principle

1. The LPC2148 initializes the LCD, RTC, keypad, switches, LEDs, and buzzer.
2. The RTC continuously provides the current date and time.
3. The current time is displayed on the LCD.
4. At the scheduled reminder time, the system displays a **"Time To Drink"** message.
5. The user presses the water-intake switch after drinking water.
6. The system records the intake and decreases the remaining glass count.
7. A successful drinking indication is displayed on the LCD.
8. If the user does not respond within the specified reminder window, the system provides a missed-reminder indication.
9. The process continues until the daily water target is reached.
10. Automatically at midnight the water intake count is reset for the next day.

## 💡 Main Features

### ⏰ RTC-Based Reminder

Uses the RTC to compare the current time with the scheduled reminder time.

### 🥛 Water Intake Tracking

Each successful button press represents one glass of water consumed.

###  LCD Display

Displays:

* Current time
* Date
* Day
* Water intake status
* Remaining glasses
* Reminder messages

### 🔴🟡🟢 LED Indication

* **Yellow LED** – Water drinking reminder
* **Red LED** – Reminder missed
* **Green LED** – Water successfully consumed

### 🔊 Buzzer Alert

Provides an audible alert during the water reminder.

### 🔢 Keypad Configuration

The matrix keypad can be used for configuring the required water intake and reminder settings.


##  System Flow

```text
        Start
          ↓
   Initialize Hardware
          ↓
     Read RTC Time
          ↓
   Display Date & Time
          ↓
   Reminder Time Reached?
       ↙          ↘
     No            Yes
     ↓              ↓
 Continue       Display Reminder
                    ↓
              Wait for User
                    ↓
             Switch Pressed?
              ↙          ↘
            Yes           No
             ↓             ↓
       Record Intake    Missed Alert
             ↓
       Decrease Count
             ↓
      Display Success
             ↓
        Continue
```

##  Applications

* Personal hydration reminders
* Smart health-monitoring systems
* Embedded reminder devices
* IoT and healthcare-related embedded projects
* Student embedded systems projects

##  Future Enhancements

* Mobile application integration
* IoT-based water intake monitoring
* Cloud-based data storage
* Personalized hydration recommendations
* Daily and weekly water intake statistics
* Bluetooth/Wi-Fi connectivity

##  Developed By

**Reddy Snehalatha**

Electronics & Communication Engineering,
Siddhartha Institute of Engineering and Technology,
Vector India

This project is developed for educational and academic purposes.

