#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include <string.h>
#include "Mylib/Serial_Cal.h"
#include "debug.h"

#define Enter 13
#define Plus '+'
#define Minus '-'
#define Multiply '*'
#define Divide '/'
#define Exponent '^'
#define Factorial '!'

char check_uart = 0;
char str[50];
char Operation;
int32_t num1=0,num2=0;
signed long Op1, Op2, Key, Sign, mul;
unsigned char msg1[] = " CALCULATOR PROGRAM";
unsigned char msg2[] = " Enter First Number: ";
unsigned char msg3[] = " Enter Second Number: ";
unsigned char msg4[] = " Enter Operation: ";
unsigned char msg5[] = " Result = ";


void InitConsole(void);
void UARTIntHandler(void);



int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);


    InitConsole();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //enable GPIO port for LED
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); //enable pin for LED PF2

    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts



    while (1) //let interrupt handler do the UART echo function
    {

        DBG("%s\n",msg1);
        DBG("%s\n",msg2);
        while (check_uart!=1);
        //Check_Number(b);
        check_uart=0;
        Check_Number(str);
        num1=atoi(str);
        //UARTprintf("%d\n",num);
        DBG("%s\n",msg4);
        while(check_uart!=1);
        //checkoper(*b);
        Check_Oper(str);
        Operation=*str;
        check_uart=0;
        DBG("%s\n",msg3);
        while(check_uart!=1);
        Check_Number(str);
        check_uart=0;
        num2=atoi(str);
        DBG("%s\n",msg5);
        switch (Operation)
        {
        case '+':
            DBG("%d\n",num1+num2);
            break;
        case '-':
            DBG("%d\n",num1-num2);
            break;
        }
    }

}

void InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

void UARTIntHandler(void)
{
    uint32_t ui32Status;
    static uint32_t i=0;
    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status

    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
    while (UARTCharsAvail(UART0_BASE)) //loop while there are chars
    {
        *(str+i)=UARTCharGetNonBlocking(UART0_BASE);
        UARTCharPutNonBlocking(UART0_BASE, *(str+i)); //echo character
        if(*(str+i)=='\n')
        {
            check_uart=1;
            *(str+i-1)='\0';
            //DBG("%c\n",*(b+i));
            i=0;
            break;
        }
        i++;
    }
    //a=1;
}
