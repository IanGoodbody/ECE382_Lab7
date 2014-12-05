# Lab 7

#### IR Sensor Interface

## Prelab

### Hardware Modifications

Because this lab will ultimately end in a moving robot in Lab 8, the control circuit for this design included the motor  
driving circuit in addition to the connections to the IR rangefinders (the IR signal sensor was included for possible 
later use). A full schematic for the design is shown below.

![alt text](Schematic)

### Software

#### IR Rangefinder Interface Design

The interface for the IR rangefinder library will allow the user to take a reading from each individual sensor, and 
include supporting functions like mean and median to allow the user to pull useful data from the rangefinder outputs. 

In order to prevent corrupted data values from drastically influencing the measurements from the sensors, the sensor 
reading functions will add their measurements to either a 4 or 8 value data buffer (depending on timing 
considerations), from which the user will be able to draw a moving mean, moving median, or some combination thereof.

The MSP430 will use its 10 bit analog to digital converter to make senes of the sensor values. Because the robot will
eventually need effective timing signals to control movement (the `waitMiliseconds()` function from lab 6) the SMCLK 
that will be used to control the timer and converter will be set to 8 MHz. This increased clock speed will require 
that every delay function within the converter itself will need to be set to the maximum to avoid loading issues. 
While the ADC can run and convert a series of signals in a single call, the modular design where each measurement 
would be taken individually requires that only one measurement be taken per call. (The IR signals were, however, wired
to the MSP430 in such a way that a sequential call would read each measurment in a desired order.) Additionally, upon 
initialization, the init function will have to fill the data buffer with measured values which could possibley be 
accomplished with this sequential read to increase speed.

Finally, if time permits, the library will include a seperate document with a mapping of IR sensor values to 
particular distances. 

#### Wall Detection System

The LED Lighting and wall detection will involve a simple call to the right and left sensor measurement functions, 
then analizing the data to see if the distances are within certain thresholds and adjusting the LED ouptput signals
accoridngly. In order to increase the speed and fidelity of the data, the program will likely make two measuremnt 
calls prior to data analysis. This will phase erronous values out faster by rotating in two new values each iteration.
It will also make the program more sensitive to drastic changes in the signal while less sensitive to corrupted values
(as fluke measurments are less likely to occure twice in a row).
