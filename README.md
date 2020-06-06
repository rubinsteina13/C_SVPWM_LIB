# C-library with implementation of the Space-Vector PWM generation technique

This embedded C-library for MCUs provides the 3-phase duty cycle generation by Space Vector Pulse Width Modulation (SVPWM) technique. [More about SVPWM technique here](https://www.switchcraft.org/learning/2017/3/15/space-vector-pwm-intro).

* Project structure
	* README.md - current file
	* LICENSE - file with license description
  * svpwm.h - C-header file with user data types and function prototypes
  * svpwm.c - C-source file with firmware functions

# HowToUse (example)

    // let it the MCU's hardware counter compare registers is: CCR0, CCR1, CCR2
    
    #include "svpwm.h"

    // updatable voltages in Alpha-Beta coordinates:
    float NewAlphaVoltage, NewBetaVoltage;

    // 1st step: create and initialize the global variable of user data structure
    tSVPWM sSVPWM = SVPWM_DEFAULTS;

    // 2nd step: do some settings
    sSVPWM.enInType = AlBe;  // set the input type
    sSVPWM.fUdc = 537.0f;    // set the DC-Link voltage in Volts
    sSVPWM.fUdcCCRval = 255; // set the Max value of counter compare register which equal to DC-Link voltage

    // 3rd step: Next code must be executed every time a new calculation of duty cycles is needed
    sSVPWM.fUal = NewAlphaVoltage;	// set a new value of voltage Alpha
    sSVPWM.fUbe = NewBetaVoltage;	// set a new value of voltage Beta
    sSVPWM.m_calc(&sSVPWM);		// call the SVPWM duty cycles calculation function
    CCR0 = sSVPWM.fCCRA;		// update the duty cycle value in CCR0
    CCR1 = sSVPWM.fCCRB;		// update the duty cycle value in CCR1
    CCR2 = sSVPWM.fCCRC;		// update the duty cycle value in CCR2

# License
  
[MIT](./LICENSE "License Description")
