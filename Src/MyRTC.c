#include "MyRTC.h"
#include "stm32f1xx.h"

/********************************************************************************************************************************/
void SetUnixTime(uint32_t Unixtime)
{
	for(uint32_t i = 0; i < 5000; i++)
	{
		if(RTC->CRL & RTC_CRL_RTOFF)
		{
			RTC->CRL |= RTC_CRL_CNF;
			RTC->CNTH = Unixtime >> 16;
			RTC->CNTL = Unixtime;
			RTC->CRL &= ~RTC_CRL_CNF;
			break;
		}
			
	}
	for(uint32_t i = 0; i < 5000; i++)
	{
		if(RTC->CRL & RTC_CRL_RTOFF)
		{
			break;
		}
	}
}
/********************************************************************************************************************************/

/********************************************************************************************************************************/
uint32_t GetUnixTime(void)
{
	for(uint32_t i = 0; i < 5000; i++)
	{
		if(RTC->CRL & RTC_CRL_RSF)
			break;
	}
	uint32_t UT = 0;
	UT = RTC->CNTH << 16;
	UT |= RTC->CNTL;
	return UT;
}
/********************************************************************************************************************************/

/****************Преобразование времени из UNIX формата формата в человекочитаемый формат****************************************/
//#pragma push
//#pragma O0
void  unixtime_to_datetime ( unsigned long unixtime, DateAndTimeTypeDef *t)
{
		unsigned long time;
		unsigned long t1;
		unsigned long a;
		unsigned long b;
		unsigned long c;
		unsigned long d;
		unsigned long e;
		unsigned long m;
		unsigned long jd;
		unsigned long jdn;
	
		jd  = ((unixtime+43200)/(86400>>1)) + (2440587<<1) + 1;
		jdn = jd>>1;

		time = unixtime;   t1 = time/60;     t->sec  = time - t1*60;
		time = t1;         t1 = time/60;     t->min  = time - t1*60;
		time = t1;         t1 = time/24;     t->hour = time - t1*24;

		 t->wday = (jdn%7)+1;

		a =  jdn + 32044;
		b = (4*a+3)/146097;
		c = a - (146097*b)/4;
		d = (4*c+3)/1461;
		e = c - (1461*d)/4;
		m = (5*e+2)/153;
		t->mday = e - (153*m+2)/5 + 1;
		t->mon  = m + 3 - 12*(m/10);
		t->year = 100*b + d - 4800 + (m/10);
		return;
}
//#pragma pop
/********************************************************************************************************************************/
/*******************************Берет время в человекочитаемом формате и возвращает время в юникс формате***********************************************************/
// DateAndTimeTypeDef* t - сюда нужно ложить время в человекочитаемом формате
// Возвращает время в юникс формате
#define _TBIAS_DAYS		((70 * (uint32_t)365) + 17)
#define	_TBIAS_YEAR		1900
#define	Daysto32(year, mon)	(((year - 1) / 4) + MONTAB(year)[mon])
#define MONTAB(year)		((((year) & 03) || ((year) == 0)) ? mos : lmos)
#pragma push
#pragma O0
uint32_t ConvertHRFtimeToUnixTime (DateAndTimeTypeDef* t)
{
	/*convert time structure to scalar time*/
	uint32_t		days;
	uint32_t		secs;
	uint16_t		mday,hour,min,sec;
	uint32_t		mon, year;
	signed short	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
	signed short	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

	/* Calculate number of days. */
	mon = t->mon;																							// Получаем месяц
	mon = mon - 1;
	year = t->year/*+2000*/;																			// Получаем год
	year = year - _TBIAS_YEAR;
	days  = Daysto32(year, mon) - 1;
	days += 365 * year;
	mday=t->mday;																							// Получаем день месяца
	days += mday;
	days -= _TBIAS_DAYS;

	/* Calculate number of seconds. */
	hour = t->hour;																						// Получаем часы
	min = t->min;																							// Получаем минуты
	sec = t->sec;																							// Получаем секунды
	secs  = 3600 * hour;
	secs += 60 * min;
	secs += sec;
	secs += (days * (uint32_t)86400);
	return secs;																								//Возвращаем время в юникс формате
}
#pragma pop
/*******************************************************************************************************************************************************************/

//*
