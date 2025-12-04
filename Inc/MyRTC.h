/**
  ******************************************************************************
  * @file    MyRTC.h
  * @brief   This file contains headers of my functions.
  ******************************************************************************
*/

 /* Define to prevent recursive inclusion -------------------------------------*/
 
#ifndef __MYRTC_H
#define __MYRTC_H

#include "stdint.h"

void SetUnixTime(uint32_t Unixtime);
uint32_t GetUnixTime(void);
typedef struct 
{ /* date and time components */
	int year;
	int mon;
	int mday;
	int wday;
	int hour;
	int min;
	int sec;
}DateAndTimeTypeDef;
void  unixtime_to_datetime ( unsigned long unixtime, DateAndTimeTypeDef *t);
uint32_t ConvertHRFtimeToUnixTime (DateAndTimeTypeDef* t);
#endif /* __MYRTC_H */
