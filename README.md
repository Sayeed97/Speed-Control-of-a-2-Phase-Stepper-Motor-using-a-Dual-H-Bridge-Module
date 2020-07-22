# Speed-Control-of-a-2-Phase-Stepper-Motor-using-a-Dual-H-Bridge-Module
This Project helps in understanding how a stepper motor works as we control the motor directly by GPIO pins using software interrupt and adjusting the frequency of the timer/counter. 
This project requires an external 12V power supply which is given to the H-Bridge to power the stepper motor (NEMA 17HS4401).
This projects uses a DSPIC33CH128MP508 Micro-Controller which is connected to a Dual H-Bridge Module using the GPIO pins. The Dual H Bridge Module is used to control the speed and direction of the 2-Phase Stepper Motor.
All the libraries included in this project is setup using MCC in mplab, which is present in the c code. 
The Micro-Controller is connected to a Explorer 16/32 Development board, which includes a on board POTentiometer. This POTentiometer can be used to vary the speed of the stepper motor. 
An Opto-coupler module (Optional) is connected to one of the GPIOs of the Micro-Controller to calculate the real-time RPM of the stepper motor.
Check the jpeg setup files to get a better idea about the Timer1, SCCP timer and ADC configuration.
IN1, IN2, IN3, IN4 named GPIO pins can be directly connected to the H-Bridge IN1, IN2, IN3, IN4 pins. Look at PIN_setup.jpeg to get a better picture about pin mapping. 
Note: do check if you have connected a common ground to all the devices in use. 

Theory: The stepper motor makes steps (1.8 degree) to make a full rotation. In this case 200 steps results in a full rotation. RPM = (1.8 degree/360)*Frequency*60. We can use this formula to calculate the frequency or time period. For example for 60 RPM the GPIO needs to perform the excitation sequence 50 times in a second. 50 times the four excitation sequence [50*4 = 200 steps]. Check the 
