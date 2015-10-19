/* ###################################################################
**     Filename    : Events.h
**     Project     : UART_HELLO_WORLD
**     Processor   : MKL46Z256VLL4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-08-28, 14:53, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Acelerometro.h"
#include "ADCs.h"
#include "AdcLdd1.h"
#include "ComGalileo.h"
#include "TU2.h"
#include "Oruga1BackwardPWM.h"
#include "PwmLdd2.h"
#include "BrazoFrontalForwardPWM.h"
#include "PwmLdd3.h"
#include "TU3.h"
#include "Oruga1ForwardPWM.h"
#include "PwmLdd1.h"
#include "Oruga2BackwardPWM.h"
#include "PwmLdd4.h"
#include "TU1.h"
#include "BrazoPostForwardPWM.h"
#include "PwmLdd8.h"
#include "Oruga2ForwardPWM.h"
#include "PwmLdd5.h"
#include "BrazoFrontalBackwardPWM.h"
#include "PwmLdd6.h"
#include "BrazoPostBackwardPWM.h"
#include "PwmLdd7.h"
#include "BateriaInput.h"
#include "BitsIoLdd1.h"
#include "Luz.h"
#include "BitIoLdd1.h"
#include "Buzzer.h"
#include "BitIoLdd2.h"
#include "Rng1Gal.h"
#include "AS1.h"
#include "MAG1.h"
#include "RingBuffer.h"
#include "GI2C1.h"
#include "WAIT1.h"
#include "CI2C1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL46Z256MC4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/*
** ===================================================================
**     Event       :  ComGalileo_OnBlockReceived (module Events)
**
**     Component   :  ComGalileo [Serial_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void ComGalileo_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  ComGalileo_OnBlockSent (module Events)
**
**     Component   :  ComGalileo [Serial_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void ComGalileo_OnBlockSent(LDD_TUserData *UserDataPtr);

void ADCs_OnEnd(void);
/*
** ===================================================================
**     Event       :  ADCs_OnEnd (module Events)
**
**     Component   :  ADCs [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void ADCs_OnCalibrationEnd(void);
/*
** ===================================================================
**     Event       :  ADCs_OnCalibrationEnd (module Events)
**
**     Component   :  ADCs [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  AS1_OnBlockReceived (module Events)
**
**     Component   :  AS1 [Serial_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void AS1_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  AS1_OnBlockSent (module Events)
**
**     Component   :  AS1 [Serial_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void AS1_OnBlockSent(LDD_TUserData *UserDataPtr);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
