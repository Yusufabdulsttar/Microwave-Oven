/* 
 * File:   mcal_interrupt_manager.c
 * Author: yusuf
 *
 * Created on April 27, 2023, 5:37 PM
 */

#include "mcal_interrupt_manager.h"
static volatile uint8 flag4=1,flag5=1,flag6=1,flag7=1;

#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE
void __interrupt() InterruptManagerHigh (void){
    if (INTERRUPT_ENABLE == INTCONbits.INT0E && INTERRUPT_OCCUR == INTCONbits.INT0IF){
        INT0_ISR();
    }
    if (INTERRUPT_ENABLE == INTCON3bits.INT2IE && INTERRUPT_OCCUR == INTCON3bits.INT2IF){
        INT2_ISR();
    }
    
} 
void __interrupt(low_priority) InterruptManagerLow (void){
    if (INTERRUPT_ENABLE == INTCON3bits.INT1IE && INTERRUPT_OCCUR == INTCON3bits.INT1IF){
        INT1_ISR();
    }
} 
#else
void __interrupt() InterruptManager (void){
    if (INTERRUPT_ENABLE == INTCONbits.INT0E && INTERRUPT_OCCUR == INTCONbits.INT0IF){
        INT0_ISR();
    }
    if (INTERRUPT_ENABLE == INTCON3bits.INT1IE && INTERRUPT_OCCUR == INTCON3bits.INT1IF){
        INT1_ISR();
    }
    if (INTERRUPT_ENABLE == INTCON3bits.INT2IE && INTERRUPT_OCCUR == INTCON3bits.INT2IF){
        INT2_ISR();
    }
    /*adc interrupt*/
    if (INTERRUPT_ENABLE == PIE1bits.ADIE && INTERRUPT_OCCUR == PIR1bits.ADIF){
        ADC_ISR();
    }
 
    /*Timer0 interrupt*/
    if (INTERRUPT_ENABLE == INTCONbits.TMR0IE && INTERRUPT_OCCUR == INTCONbits.TMR0IF){
        TIMER_ISR();
    }
    
    /*Timer1 interrupt*/
    if (INTERRUPT_ENABLE == PIE1bits.TMR1IE && INTERRUPT_OCCUR == PIR1bits.TMR1IF){
        TIMER1_ISR();
    }

    /*Timer2 interrupt*/
    if (INTERRUPT_ENABLE == PIE1bits.TMR2IE && INTERRUPT_OCCUR == PIR1bits.TMR2IF){
        TIMER2_ISR();
    }
    
    /*Timer3 interrupt*/
    if (INTERRUPT_ENABLE == PIE2bits.TMR3IE && INTERRUPT_OCCUR == PIR2bits.TMR3IF){
        TIMER3_ISR();
    }
    /*CCP1 interrupt*/
    if (INTERRUPT_ENABLE == PIE1bits.CCP1IE && INTERRUPT_OCCUR == PIR1bits.CCP1IF){
        CCP1_ISR();
    }
    /*CCP2 interrupt*/
    if (INTERRUPT_ENABLE == PIE2bits.CCP2IE && INTERRUPT_OCCUR == PIR2bits.CCP2IF){
        CCP2_ISR();
    }
    
    /*usart tx interrupt*/
    if (INTERRUPT_ENABLE == PIE1bits.TX1IE && INTERRUPT_OCCUR == PIR1bits.TXIF){
        USART_TX_ISR();
    }
    /*usart rx interrupt*/
    if (INTERRUPT_ENABLE == PIE1bits.RCIE && INTERRUPT_OCCUR == PIR1bits.RCIF){
        USART_RX_ISR();
    }
    
    /*spi & i2c interrupt*/
    if (INTERRUPT_ENABLE == PIE1bits.SSPIE && INTERRUPT_OCCUR == PIR1bits.SSPIF){
        SPI_ISR();
        I2C_ISR();
    }
    /*i2c bus col interrupt*/
    if (INTERRUPT_ENABLE == PIE2bits.BCLIE && INTERRUPT_OCCUR == PIR2bits.BCLIF){
        I2C_BUS_COL_ISR();
    }
    
    if (INTERRUPT_ENABLE == INTCONbits.RBIE && INTERRUPT_OCCUR == INTCONbits.RBIF && HIGH == PORTBbits.RB4 && flag4 == 1){
        flag4 = 0;
        RB4_ISR(1);
    }
    if (INTERRUPT_ENABLE == INTCONbits.RBIE && INTERRUPT_OCCUR == INTCONbits.RBIF && LOW == PORTBbits.RB4 && flag4 == 0){
        flag4 = 1;
        RB4_ISR(0);
    }
    if (INTERRUPT_ENABLE == INTCONbits.RBIE && INTERRUPT_OCCUR == INTCONbits.RBIF && HIGH == PORTBbits.RB5 && flag5 == 1){
        flag5 = 0;
        RB5_ISR(1);
    }
    if (INTERRUPT_ENABLE == INTCONbits.RBIE && INTERRUPT_OCCUR == INTCONbits.RBIF && LOW == PORTBbits.RB5 && flag5 == 0){
        flag5 = 1;
        RB5_ISR(0);
    }
    if (INTERRUPT_ENABLE == INTCONbits.RBIE && INTERRUPT_OCCUR == INTCONbits.RBIF && HIGH == PORTBbits.RB6 && flag6 == 1){
        flag6 = 0;
        RB6_ISR(1);
    }
    if (INTERRUPT_ENABLE == INTCONbits.RBIE && INTERRUPT_OCCUR == INTCONbits.RBIF && LOW == PORTBbits.RB6 && flag6 == 0){
        flag6 = 1;
        RB6_ISR(0);
    }
    if (INTERRUPT_ENABLE == INTCONbits.RBIE && INTERRUPT_OCCUR == INTCONbits.RBIF && HIGH == PORTBbits.RB7 && flag7 == 1){
        flag7 = 0;
        RB7_ISR(1);
    }
    if (INTERRUPT_ENABLE == INTCONbits.RBIE && INTERRUPT_OCCUR == INTCONbits.RBIF && LOW == PORTBbits.RB7 && flag7 == 0){
        flag7 = 1;
        RB7_ISR(0);
    }
}
#endif