/*
*********************************************************************************************************
*                                                MeDEf
*                                         Medidor de Eficiencia
*                                            
*
*
* File : dsPIC_cfg.C
*
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                       MPLAB CONFIGURATION MACROS
*********************************************************************************************************
*/

    //__CONFIG(FWDT, WDTDIS);                                             /* Disable the watchdog timer                               */
    //__CONFIG(FOSCSEL, OSCPLL);                                          /* Enable the primary XT / HS oscillator with PLL           */
		
		//_FOSC( POSCMD_NONE & OSCIOFNC_OFF)
		//_FOSCSEL( FNOSC_FRCPLL & IESO_OFF);

		_FWDT( FWDTEN_OFF & WDTPRE_PR32 & WDTPOST_PS1 );
		_FOSC( POSCMD_HS & OSCIOFNC_OFF );
		_FOSCSEL( FNOSC_PRIPLL & IESO_OFF );

/*
*********************************************************************************************************
*                                              CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

static  void  PLL_Init(void);
static  void  Tmr_TickInit(void);

/*
*********************************************************************************************************
*                                         BSP INITIALIZATION
*
* Description : This function should be called by your application code before you make use of any of the
*               functions found in this module.
*
* Arguments   : none
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    RCON    &= ~SWDTEN;                                                 /* Ensure Watchdog disabled via IDE CONFIG bits and SW.     */

    PLL_Init();                                                     /* Initialize the PLL                                       */     
    Tmr_TickInit();                                                     /* Initialize the uC/OS-II tick interrupt                   */
}

/*
*********************************************************************************************************
*                                      PLL_Init()
*
* Description : This function configures and enables the PLL with the external oscillator
*               selected as the input clock to the PLL.
*
* Notes       : 1) The PLL output frequency is calculated by FIN * (M / (N1 * N2)).
*               2) FIN is the PLL input clock frequency, defined in bsp.h as
*                  CPU_PRIMARY_OSC_FR. This is the same as the external primary
*                  oscillator on the Explorer 16 Evaluation Board.
*               3) M is the desired PLL multiplier
*               4) N1 is the divider for FIN before FIN enters the PLL block (Pre-Divider)
*               5) N2 is the PLL output divider (Post-Divider)
*
* Summary     :    The PLL is configured as (8MHZ) * (40 / (2 * 2)) = 80MHZ
*                  The processor clock is (1/2) of the PLL output.
*                  Performance = 40 MIPS.
*********************************************************************************************************
*/

static  void  PLL_Init (void)
{
		
		//Frecuencia del Cristal = Fin = 10 MHz
		//Ajustamos el PLL para tener Fosc = 79.608.000 Hz
		//Fcy = Fosc/2 = 39.804.000 Hz
		//Tcy = 1/Fcy = 25.123 ns
		CLKDIVbits.PLLPRE = 8;		//Dividimos en 10 la frecuencia del cristal
		DelayTcy(10);
    PLLFBDbits.PLLDIV = 158; //PLLFBDbits.PLLDIV = 158;	//Multiplicamos por M=160 
		DelayTcy(10);                                             
		CLKDIVbits.PLLPOST = 0x00; //Dividimos por 2
		DelayTcy(10);  
		CLKDIVbits.DOZE = 0x00;        
		
		//PLLFBD   =     38;                                                  /* Set the Multiplier (M) to 40 (2 added automatically) 	*/
    //CLKDIV   =      0;                                                  /* Clear the PLL Pre Divider bits, N1 = N2 = 2              */                                     
}

/*
*********************************************************************************************************
*                                      BSP_CPU_ClkFrq()

* Description : This function determines the CPU clock frequency (Fcy)
* Returns     : The CPU frequency in (HZ)
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFrq (void)
{
    CPU_INT08U  Clk_Selected;
    CPU_INT08U  PLL_n1;
    CPU_INT08U  PLL_n2;
    CPU_INT16U  PLL_m;
    CPU_INT16U  FRC_Div;
    CPU_INT32U  CPU_Clk_Frq;


    PLL_m         =  (PLLFBD & PLLDIV_MASK) + 2;                        /* Get the Multiplier value                                 */
    PLL_n1        =  (CLKDIV & PLLPRE_MASK) + 2;                        /* Computer the Pre Divider value                           */
    PLL_n2        = ((CLKDIV & PLLPOST_MASK) >> 6);                     /* Get the Post Divider register value                      */
    PLL_n2        = ((PLL_n2 * 2) + 2);                                 /* Compute the Post Divider value                           */

    FRC_Div       = ((CLKDIV & FRCDIV_MASK) >> 8);                      /* Get the FRC Oscillator Divider register value            */
    FRC_Div       = ((1 << FRC_Div) * 2);                               /* Compute the FRC Divider value                            */

    Clk_Selected  =  (OSCCON & COSC_MASK) >> 12;                        /* Determine which clock source is currently selected       */

    switch (Clk_Selected) {
        case 0:                                                         /* Fast Oscillator (FRC) Selected                           */
        case 7:
             CPU_Clk_Frq   =   CPU_FRC_OSC_FRQ;                         /* Return the frequency of the internal fast oscillator     */
             break;

        case 1:                                                         /* Fast Oscillator (FRC) with PLL Selected                  */
             CPU_Clk_Frq   = ((CPU_FRC_OSC_FRQ  * PLL_m) /              /* Compute the PLL output frequency using the FRC as FIN    */
                              (FRC_Div * PLL_n1 * PLL_n2));
             break;

        case 2:                                                         /* Primary External Oscillator Selected                     */
             CPU_Clk_Frq   =   CPU_PRIMARY_OSC_FRQ;                     /* Return the frequency of the primary external oscillator  */
             break;

        case 3:                                                         /* Primary External Oscillator with PLL Selected            */
             CPU_Clk_Frq   = ((CPU_PRIMARY_OSC_FRQ * PLL_m) /           /* Compute the PLL output frq using the PRI EXT OSC as FIN  */
                              (PLL_n1 * PLL_n2));
             break;

        case 4:                                                         /* Secondary External Low Power Oscillator (SOSC) Selected  */
        case 5:                                                         /* Internal Low Power RC Oscillator Selected                */
             CPU_Clk_Frq   =   CPU_SECONDARY_OSC_FRQ;                   /* Return the frq of the external secondary Low Power OSC   */
             break;

        case 6:
             CPU_Clk_Frq = 0;                                           /* Return 0 for the Reserved clock setting                  */
             break;

        default:
             CPU_Clk_Frq = 0;                                           /* Return 0 if the clock source cannot be determined        */
             break;
    }

    CPU_Clk_Frq   /=  2;                                                /* Divide the final frq by 2, get the actual CPU Frq (Fcy)  */

    return (CPU_Clk_Frq);                                               /* Return the operating frequency                           */
}

/*
*********************************************************************************************************
*                                     DISABLE ALL INTERRUPTS
*
* Description : This function disables all interrupts from the interrupt controller.
*
* Arguments   : none
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{
	SRbits.IPL = 0b111;
}

/*
*********************************************************************************************************
*                                       TICKER INITIALIZATION
*
* Description : This function is called to initialize uC/OS-II's tick source (typically a timer generating
*               interrupts every 1 to 100 mS).
*
* Arguments   : none
*
* Note(s)     : 1) The timer operates at a frequency of Fosc / 4
*               2) The timer resets to 0 after period register match interrupt is generated
*********************************************************************************************************
*/

static  void  Tmr_TickInit (void)
{
    CPU_INT32U  tmr_frq;
    CPU_INT16U  cnts;


    //tmr_frq   =   BSP_CPU_ClkFrq();                                     /* Get the CPU Clock Frequency (Hz) (Fcy)                   */
    //tmr_frq   =   39804000;
		//cnts      =   (tmr_frq / OS_TICKS_PER_SEC) - 1;                     /* Calaculate the number of timer ticks between interrupts  */

#if BSP_OS_TMR_SEL == 2
    T2CON     =   0;                                                    /* Use Internal Osc (Fcy), 16 bit mode, prescaler = 1  		*/
    TMR2      =   0;                                                    /* Start counting from 0 and clear the prescaler count      */
    T2CONbits.TCKPS = 0;	//Prescaler divide por 8
		//PR2       =   cnts;                                                 /* Set the period register                                  */
    //PR2       =   2498;		//Pres = 8 => 1000.3 ticks por segundo
		PR2       =   19996;		//Pres = 1 => 1000.0 ticks por segundo
		IPC1     &=  ~T2IP_MASK;                                            /* Clear all timer 2 interrupt priority bits                */
    IPC1     |=  (TIMER_INT_PRIO << 12);                                /* Set timer 2 to operate with an interrupt priority of 4   */
    IFS0     &=  ~T2IF;                                                 /* Clear the interrupt for timer 2                          */
    IEC0     |=   T2IE;                                                 /* Enable interrupts for timer 2                            */
    T2CON    |=   TON;                                                  /* Start the timer                                          */
#endif

#if BSP_OS_TMR_SEL == 4
    T4CON     =   0;                                                    /* Use Internal Osc (Fcy), 16 bit mode, prescaler = 1  		*/
    TMR4      =   0;                                                    /* Start counting from 0 and clear the prescaler count      */
    PR4       =   cnts;                                                 /* Set the period register                                  */
    IPC6     &=  ~T4IP_MASK;                                            /* Clear all timer 4 interrupt priority bits                */
    IPC6     |=  (TIMER_INT_PRIO << 12);                                /* Set timer 4 to operate with an interrupt priority of 4   */
    IFS1     &=  ~T4IF;                                                 /* Clear the interrupt for timer 4                          */
    IEC1     |=   T4IE;                                                 /* Enable interrupts for timer 4                            */
    T4CON    |=   TON;                                                  /* Start the timer                                          */
#endif
}

/*
*********************************************************************************************************
*                                     OS TICK INTERRUPT SERVICE ROUTINE
*
* Description : This function handles the timer interrupt that is used to generate TICKs for uC/OS-II.
*********************************************************************************************************
*/

void OS_Tick_ISR_Handler (void)
{
#if  BSP_OS_TMR_SEL == 2
    IFS0 &= ~T2IF;
#endif

#if  BSP_OS_TMR_SEL == 4
    IFS1 &= ~T41F;
#endif

    OSTimeTick();
}

