/*
 * Serial_Cal.h
 *
 *  Created on: Jul 11, 2020
 *      Author: LV_Embedded
 *      nguyenlamvien0110@gmail.com
 *      https://github.com/vien20010
 */

#include "Serial_Cal.h"



void baoloi()
{
    DBG("Loi roi bro reset va lam lai di\n");
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //blink LED
    while(1)
    {
    }
}
void Check_Number(char *data)
{
    uint16_t j;
    for (j=1;*(data+j)!='\0';j++)
    {
        if ((*(data+j)<'0')||(*(data+j)>'9'))
            baoloi();
    }
}
void Check_Oper(char *data)
{
    if (*(data+1)!='\0')
        baoloi();
    if (!((*data=='+')||(*data=='-')||(*data=='*')||(*data=='/')))
        baoloi();
}
