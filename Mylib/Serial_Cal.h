/*
 * Serial_Cal.h
 *
 *  Created on: Jul 11, 2020
 *      Author: LV_Embedded
 *      nguyenlamvien0110@gmail.com
 *      https://github.com/vien20010
 */

#ifndef MYLIB_SERIAL_CAL_H_
#define MYLIB_SERIAL_CAL_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "debug.h"

void baoloi();
void Check_Number(char *data);
void Check_Oper(char *data);

#endif /* MYLIB_SERIAL_CAL_H_ */
