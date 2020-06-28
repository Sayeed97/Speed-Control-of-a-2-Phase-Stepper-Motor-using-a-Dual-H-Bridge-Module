/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.167.0
        Device            :  dsPIC33CH128MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.35
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/sccp1_tmr.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/adc1.h"

/*
                         Main application
 */

void sensor_status(void) 
{
    _LATE3 = 1; //latch_E3 is used as a flag to calculate RPM, is set to 1 or High 
}

void delay(void) //defining a user defined delay using a timer
{
    bool status = true;
    SCCP1_TMR_Start();
    
    while(status)
    {
        SCCP1_TMR_SecondaryTimerTasks();
        if(SCCP1_TMR_SecondaryTimer16ElapsedThenClear() == true)
        {
            SCCP1_TMR_Stop();
            status = false;
        }
    }
}

int main(void)
{
    /*Initialize the device*/
    SYSTEM_Initialize();
    ADC1_Enable();
    ADC1_ChannelSelect(channel_AN0);
    /*Timer interrupt for RPM count*/
    TMR1_SetInterruptHandler(sensor_status); //after every 60 seconds the Interrupt handler will point to the location of sensor_status function
    TMR1_Start();
    _LATE3 = 0; //by default the latch is set to 0 or Low 
    uint16_t sensor_value = 0; //used for detecting an input from the opto-coupler 
    uint16_t rpm_count = 0; //used in rpm calculation 
    uint16_t rpm = 0; //rpm value 
    uint16_t value = 0; //ADC value of POT 
    while (1)
    {   
        ADC1_SoftwareTriggerEnable();
        SCCP1_TMR_Counter16BitSecondarySet(10);
        delay();
        ADC1_SoftwareTriggerDisable();
        if(ADC1_IsConversionComplete(channel_AN0))
        {
            value = 4296 - ADC1_ConversionResultGet(channel_AN0); //mapping between the ADC value of POT and the delay used for making steps in the stepper motor
        }
        SCCP1_TMR_Counter16BitSecondarySet(value); //delay value is set
        
        /*RPM calculation*/
		
        if(_LATE3!=0)
        {
            rpm = rpm_count/2; //use of an encoder wheel with two holes
            rpm_count = 0; //resetting of rpm_count to count for the next 60s
            _LATE3 = 0; //latch_E3 status is reset 
        }
          
        /*Makes the stepper move 1.8 degree clockwise direction*/

        IN1_SetHigh();
        IN2_SetLow();
        IN3_SetLow();
        IN4_SetLow();
        
        /*Sensing part*/
        
        sensor_value = Sensor_GetValue();
        if(sensor_value != 0)
        {
            if(_LATE2 != 1) //latch_E2 is used as a status for avoiding miscounting 
            {
                _LATE2 = 1;
                rpm_count++;
            }
        }
        if(sensor_value == 0)
        {
            if(_LATE2 != 0)
            {
                _LATE2 = 0;
            }
        }

        delay();

        /*Makes the stepper move 1.8 degree clockwise direction*/

        IN3_SetHigh();
        IN1_SetLow();
        IN2_SetLow();
        IN4_SetLow();
        
        /*Sensing part*/
        
        sensor_value = Sensor_GetValue();
        if(sensor_value != 0)
        {
            if(_LATE2 != 1) //latch_E2 is used as a status for avoiding miscounting
            {
                _LATE2 = 1;
                rpm_count++;
            }
        }
        if(sensor_value == 0)
        {
            if(_LATE2 != 0)
            {
                _LATE2 = 0;
            }
        }

        delay();

        /*Makes the stepper move 1.8 degree clockwise direction*/

        IN2_SetHigh();
        IN1_SetLow();
        IN3_SetLow();
        IN4_SetLow();
        
        /*Sensing part*/
        
        sensor_value = Sensor_GetValue();
        if(sensor_value != 0)
        {
            if(_LATE2 != 1) //latch_E2 is used as a status for avoiding miscounting
            {
                _LATE2 = 1;
                rpm_count++;
            }
        }
        if(sensor_value == 0)
        {
            if(_LATE2 != 0)
            {
                _LATE2 = 0;
            }
        }

        delay();

        /*Makes the stepper move 1.8 degree clockwise direction*/

        IN4_SetHigh();
        IN1_SetLow();
        IN2_SetLow();
        IN3_SetLow();
        
        /*Sensing part*/
        
        sensor_value = Sensor_GetValue();
        if(sensor_value != 0)
        {
            if(_LATE2 != 1) //latch_E2 is used as a status for avoiding miscounting
            {
                _LATE2 = 1;
                rpm_count++;
            }
        }
        if(sensor_value == 0)
        {
            if(_LATE2 != 0)
            {
                _LATE2 = 0;
            }
        }

        delay();
        
    }
    return 1; 
}
/**
 End of File
*/