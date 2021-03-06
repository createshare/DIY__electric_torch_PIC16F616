
#ifndef	_HTC_H_
#warning Header file pic16f616.h included directly. Use #include <htc.h> instead.
#endif

/* header file for the MICROCHIP PIC microcontroller
 *  16F616
 */


#ifndef __PIC16F616_H
#define __PIC16F616_H

//
// Configuration mask definitions
//


// Config Register: CONFIG
#define CONFIG               0x2007
// Oscillator Selection bits
// RC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN
#define FOSC_EXTRCCLK        0xFFFF
// RCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN
#define FOSC_EXTRCIO         0xFFFE
// INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
#define FOSC_INTOSCCLK       0xFFFD
// INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
#define FOSC_INTOSCIO        0xFFFC
// EC: I/O function on RA4/OSC2/CLKOUT pin, CLKIN on RA5/OSC1/CLKIN
#define FOSC_EC              0xFFFB
// HS oscillator: High-speed crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
#define FOSC_HS              0xFFFA
// XT oscillator: Crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
#define FOSC_XT              0xFFF9
// LP oscillator: Low-power crystal on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
#define FOSC_LP              0xFFF8
// Watchdog Timer Enable bit
// WDT enabled
#define WDTE_ON              0xFFFF
// WDT disabled and can be enabled by SWDTEN bit of the WDTCON register
#define WDTE_OFF             0xFFF7
// Power-up Timer Enable bit
// PWRT disabled
#define PWRTE_OFF            0xFFFF
// PWRT enabled
#define PWRTE_ON             0xFFEF
// MCLR Pin Function Select bit
// MCLR pin function is MCLR
#define MCLRE_ON             0xFFFF
// MCLR pin function is digital input, MCLR internally tied to VDD
#define MCLRE_OFF            0xFFDF
// Code Protection bit
// Program memory code protection is disabled
#define CP_OFF               0xFFFF
// Program memory code protection is enabled
#define CP_ON                0xFFBF
// Internal Oscillator Frequency Select bit
// 8 MHz
#define IOSCFS_8MHZ          0xFFFF
// 4 MHz
#define IOSCFS_4MHZ          0xFF7F
// Brown-out Reset Selection bits
// BOR enabled
#define BOREN_ON             0xFFFF
// BOR enabled during operation and disabled in Sleep
#define BOREN_NSLEEP         0xFEFF
// BOR Disabled
#define BOREN_OFF            0xFCFF


//
// Special function register definitions
//


// Register: INDF
volatile unsigned char           INDF                @ 0x000;
// bit and bitfield definitions

// Register: TMR0
volatile unsigned char           TMR0                @ 0x001;
// bit and bitfield definitions

// Register: PCL
volatile unsigned char           PCL                 @ 0x002;
// bit and bitfield definitions

// Register: STATUS
volatile unsigned char           STATUS              @ 0x003;
// bit and bitfield definitions
volatile bit CARRY               @ ((unsigned)&STATUS*8)+0;
volatile bit DC                  @ ((unsigned)&STATUS*8)+1;
volatile bit ZERO                @ ((unsigned)&STATUS*8)+2;
volatile bit nPD                 @ ((unsigned)&STATUS*8)+3;
volatile bit nTO                 @ ((unsigned)&STATUS*8)+4;
volatile bit IRP                 @ ((unsigned)&STATUS*8)+7;
volatile bit RP0                 @ ((unsigned)&STATUS*8)+5;
volatile bit RP1                 @ ((unsigned)&STATUS*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	C                   : 1;
        unsigned	DC                  : 1;
        unsigned	Z                   : 1;
        unsigned	nPD                 : 1;
        unsigned	nTO                 : 1;
        unsigned	RP                  : 2;
        unsigned	IRP                 : 1;
    };
    struct {
        unsigned	                    : 5;
        unsigned	RP0                 : 1;
        unsigned	RP1                 : 1;
    };
} STATUSbits @ 0x003;
#endif

// Register: FSR
volatile unsigned char           FSR                 @ 0x004;
// bit and bitfield definitions

// Register: PORTA
volatile unsigned char           PORTA               @ 0x005;
// bit and bitfield definitions
volatile bit RA0                 @ ((unsigned)&PORTA*8)+0;
volatile bit RA1                 @ ((unsigned)&PORTA*8)+1;
volatile bit RA2                 @ ((unsigned)&PORTA*8)+2;
volatile bit RA3                 @ ((unsigned)&PORTA*8)+3;
volatile bit RA4                 @ ((unsigned)&PORTA*8)+4;
volatile bit RA5                 @ ((unsigned)&PORTA*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RA0                 : 1;
        unsigned	RA1                 : 1;
        unsigned	RA2                 : 1;
        unsigned	RA3                 : 1;
        unsigned	RA4                 : 1;
        unsigned	RA5                 : 1;
    };
} PORTAbits @ 0x005;
#endif

// Register: PORTC
volatile unsigned char           PORTC               @ 0x007;
// bit and bitfield definitions
volatile bit RC0                 @ ((unsigned)&PORTC*8)+0;
volatile bit RC1                 @ ((unsigned)&PORTC*8)+1;
volatile bit RC2                 @ ((unsigned)&PORTC*8)+2;
volatile bit RC3                 @ ((unsigned)&PORTC*8)+3;
volatile bit RC4                 @ ((unsigned)&PORTC*8)+4;
volatile bit RC5                 @ ((unsigned)&PORTC*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RC0                 : 1;
        unsigned	RC1                 : 1;
        unsigned	RC2                 : 1;
        unsigned	RC3                 : 1;
        unsigned	RC4                 : 1;
        unsigned	RC5                 : 1;
    };
} PORTCbits @ 0x007;
#endif

// Register: PCLATH
volatile unsigned char           PCLATH              @ 0x00A;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PCLATH              : 5;
    };
} PCLATHbits @ 0x00A;
#endif

// Register: INTCON
volatile unsigned char           INTCON              @ 0x00B;
// bit and bitfield definitions
volatile bit RAIF                @ ((unsigned)&INTCON*8)+0;
volatile bit INTF                @ ((unsigned)&INTCON*8)+1;
volatile bit TMR0IF              @ ((unsigned)&INTCON*8)+2;
volatile bit RAIE                @ ((unsigned)&INTCON*8)+3;
volatile bit INTE                @ ((unsigned)&INTCON*8)+4;
volatile bit TMR0IE              @ ((unsigned)&INTCON*8)+5;
volatile bit PEIE                @ ((unsigned)&INTCON*8)+6;
volatile bit GIE                 @ ((unsigned)&INTCON*8)+7;
volatile bit T0IF                @ ((unsigned)&INTCON*8)+2;
volatile bit T0IE                @ ((unsigned)&INTCON*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RAIF                : 1;
        unsigned	INTF                : 1;
        unsigned	TMR0IF              : 1;
        unsigned	RAIE                : 1;
        unsigned	INTE                : 1;
        unsigned	TMR0IE              : 1;
        unsigned	PEIE                : 1;
        unsigned	GIE                 : 1;
    };
    struct {
        unsigned	                    : 2;
        unsigned	T0IF                : 1;
        unsigned	: 2;
        unsigned	T0IE                : 1;
    };
} INTCONbits @ 0x00B;
#endif

// Register: PIR1
volatile unsigned char           PIR1                @ 0x00C;
// bit and bitfield definitions
volatile bit TMR1IF              @ ((unsigned)&PIR1*8)+0;
volatile bit TMR2IF              @ ((unsigned)&PIR1*8)+1;
volatile bit C1IF                @ ((unsigned)&PIR1*8)+3;
volatile bit C2IF                @ ((unsigned)&PIR1*8)+4;
volatile bit ECCPIF              @ ((unsigned)&PIR1*8)+5;
volatile bit ADIF                @ ((unsigned)&PIR1*8)+6;
volatile bit T1IF                @ ((unsigned)&PIR1*8)+0;
volatile bit T2IF                @ ((unsigned)&PIR1*8)+1;
volatile bit CCP1IF              @ ((unsigned)&PIR1*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR1IF              : 1;
        unsigned	TMR2IF              : 1;
        unsigned	                    : 1;
        unsigned	C1IF                : 1;
        unsigned	C2IF                : 1;
        unsigned	ECCPIF              : 1;
        unsigned	ADIF                : 1;
    };
    struct {
        unsigned	T1IF                : 1;
        unsigned	T2IF                : 1;
        unsigned	: 3;
        unsigned	CCP1IF              : 1;
    };
} PIR1bits @ 0x00C;
#endif
// bit and bitfield definitions

// Register: TMR1L
volatile unsigned char           TMR1L               @ 0x00E;
// bit and bitfield definitions

// Register: TMR1H
volatile unsigned char           TMR1H               @ 0x00F;
// bit and bitfield definitions

// Register: TMR1
volatile unsigned int            TMR1                @ 0x00E;

// Register: T1CON
volatile unsigned char           T1CON               @ 0x010;
// bit and bitfield definitions
volatile bit TMR1ON              @ ((unsigned)&T1CON*8)+0;
volatile bit TMR1CS              @ ((unsigned)&T1CON*8)+1;
volatile bit nT1SYNC             @ ((unsigned)&T1CON*8)+2;
volatile bit T1OSCEN             @ ((unsigned)&T1CON*8)+3;
volatile bit TMR1GE              @ ((unsigned)&T1CON*8)+6;
volatile bit T1GINV              @ ((unsigned)&T1CON*8)+7;
volatile bit T1CKPS0             @ ((unsigned)&T1CON*8)+4;
volatile bit T1CKPS1             @ ((unsigned)&T1CON*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR1ON              : 1;
        unsigned	TMR1CS              : 1;
        unsigned	nT1SYNC             : 1;
        unsigned	T1OSCEN             : 1;
        unsigned	T1CKPS              : 2;
        unsigned	TMR1GE              : 1;
        unsigned	T1GINV              : 1;
    };
    struct {
        unsigned	                    : 4;
        unsigned	T1CKPS0             : 1;
        unsigned	T1CKPS1             : 1;
    };
} T1CONbits @ 0x010;
#endif

// Register: TMR2
volatile unsigned char           TMR2                @ 0x011;
// bit and bitfield definitions

// Register: T2CON
volatile unsigned char           T2CON               @ 0x012;
// bit and bitfield definitions
volatile bit TMR2ON              @ ((unsigned)&T2CON*8)+2;
volatile bit T2CKPS0             @ ((unsigned)&T2CON*8)+0;
volatile bit T2CKPS1             @ ((unsigned)&T2CON*8)+1;
volatile bit TOUTPS0             @ ((unsigned)&T2CON*8)+3;
volatile bit TOUTPS1             @ ((unsigned)&T2CON*8)+4;
volatile bit TOUTPS2             @ ((unsigned)&T2CON*8)+5;
volatile bit TOUTPS3             @ ((unsigned)&T2CON*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKPS              : 2;
        unsigned	TMR2ON              : 1;
        unsigned	TOUTPS              : 4;
    };
    struct {
        unsigned	T2CKPS0             : 1;
        unsigned	T2CKPS1             : 1;
        unsigned	                    : 1;
        unsigned	TOUTPS0             : 1;
        unsigned	TOUTPS1             : 1;
        unsigned	TOUTPS2             : 1;
        unsigned	TOUTPS3             : 1;
    };
} T2CONbits @ 0x012;
#endif
// bit and bitfield definitions

// Register: CCPR1L
volatile unsigned char           CCPR1L              @ 0x013;
// bit and bitfield definitions

// Register: CCPR1H
volatile unsigned char           CCPR1H              @ 0x014;
// bit and bitfield definitions

// Register: CCPR1
volatile unsigned int            CCPR1               @ 0x013;

// Register: CCP1CON
volatile unsigned char           CCP1CON             @ 0x015;
// bit and bitfield definitions
volatile bit CCP1M0              @ ((unsigned)&CCP1CON*8)+0;
volatile bit CCP1M1              @ ((unsigned)&CCP1CON*8)+1;
volatile bit CCP1M2              @ ((unsigned)&CCP1CON*8)+2;
volatile bit CCP1M3              @ ((unsigned)&CCP1CON*8)+3;
volatile bit DC1B0               @ ((unsigned)&CCP1CON*8)+4;
volatile bit DC1B1               @ ((unsigned)&CCP1CON*8)+5;
volatile bit P1M0                @ ((unsigned)&CCP1CON*8)+6;
volatile bit P1M1                @ ((unsigned)&CCP1CON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CCP1M               : 4;
        unsigned	DCB                 : 2;
        unsigned	PM                  : 2;
    };
    struct {
        unsigned	CCP1M0              : 1;
        unsigned	CCP1M1              : 1;
        unsigned	CCP1M2              : 1;
        unsigned	CCP1M3              : 1;
        unsigned	DC1B0               : 1;
        unsigned	DC1B1               : 1;
        unsigned	P1M0                : 1;
        unsigned	P1M1                : 1;
    };
} CCP1CONbits @ 0x015;
#endif

// Register: PWM1CON
volatile unsigned char           PWM1CON             @ 0x016;
// bit and bitfield definitions
volatile bit PRSEN               @ ((unsigned)&PWM1CON*8)+7;
volatile bit PDC0                @ ((unsigned)&PWM1CON*8)+0;
volatile bit PDC1                @ ((unsigned)&PWM1CON*8)+1;
volatile bit PDC2                @ ((unsigned)&PWM1CON*8)+2;
volatile bit PDC3                @ ((unsigned)&PWM1CON*8)+3;
volatile bit PDC4                @ ((unsigned)&PWM1CON*8)+4;
volatile bit PDC5                @ ((unsigned)&PWM1CON*8)+5;
volatile bit PDC6                @ ((unsigned)&PWM1CON*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PDC                 : 7;
        unsigned	PRSEN               : 1;
    };
    struct {
        unsigned	PDC0                : 1;
        unsigned	PDC1                : 1;
        unsigned	PDC2                : 1;
        unsigned	PDC3                : 1;
        unsigned	PDC4                : 1;
        unsigned	PDC5                : 1;
        unsigned	PDC6                : 1;
    };
} PWM1CONbits @ 0x016;
#endif

// Register: ECCPAS
volatile unsigned char           ECCPAS              @ 0x017;
// bit and bitfield definitions
volatile bit ECCPASE             @ ((unsigned)&ECCPAS*8)+7;
volatile bit PSSBD0              @ ((unsigned)&ECCPAS*8)+0;
volatile bit PSSBD1              @ ((unsigned)&ECCPAS*8)+1;
volatile bit PSSAC0              @ ((unsigned)&ECCPAS*8)+2;
volatile bit PSSAC1              @ ((unsigned)&ECCPAS*8)+3;
volatile bit ECCPAS0             @ ((unsigned)&ECCPAS*8)+4;
volatile bit ECCPAS1             @ ((unsigned)&ECCPAS*8)+5;
volatile bit ECCPAS2             @ ((unsigned)&ECCPAS*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSSBD               : 2;
        unsigned	PSSAC               : 2;
        unsigned	ECCPAS              : 3;
        unsigned	ECCPASE             : 1;
    };
    struct {
        unsigned	PSSBD0              : 1;
        unsigned	PSSBD1              : 1;
        unsigned	PSSAC0              : 1;
        unsigned	PSSAC1              : 1;
        unsigned	ECCPAS0             : 1;
        unsigned	ECCPAS1             : 1;
        unsigned	ECCPAS2             : 1;
    };
} ECCPASbits @ 0x017;
#endif

// Register: VRCON
volatile unsigned char           VRCON               @ 0x019;
// bit and bitfield definitions
volatile bit VP6EN               @ ((unsigned)&VRCON*8)+4;
volatile bit VRR                 @ ((unsigned)&VRCON*8)+5;
volatile bit C2VREN              @ ((unsigned)&VRCON*8)+6;
volatile bit C1VREN              @ ((unsigned)&VRCON*8)+7;
volatile bit VR0                 @ ((unsigned)&VRCON*8)+0;
volatile bit VR1                 @ ((unsigned)&VRCON*8)+1;
volatile bit VR2                 @ ((unsigned)&VRCON*8)+2;
volatile bit VR3                 @ ((unsigned)&VRCON*8)+3;
volatile bit FVREN               @ ((unsigned)&VRCON*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	VR                  : 4;
        unsigned	VP6EN               : 1;
        unsigned	VRR                 : 1;
        unsigned	C2VREN              : 1;
        unsigned	C1VREN              : 1;
    };
    struct {
        unsigned	VR0                 : 1;
        unsigned	VR1                 : 1;
        unsigned	VR2                 : 1;
        unsigned	VR3                 : 1;
        unsigned	FVREN               : 1;
    };
} VRCONbits @ 0x019;
#endif

// Register: CM1CON0
volatile unsigned char           CM1CON0             @ 0x01A;
// bit and bitfield definitions
volatile bit C1R                 @ ((unsigned)&CM1CON0*8)+2;
volatile bit C1POL               @ ((unsigned)&CM1CON0*8)+4;
volatile bit C1OE                @ ((unsigned)&CM1CON0*8)+5;
volatile bit C1OUT               @ ((unsigned)&CM1CON0*8)+6;
volatile bit C1ON                @ ((unsigned)&CM1CON0*8)+7;
volatile bit C1CH0               @ ((unsigned)&CM1CON0*8)+0;
volatile bit C1CH1               @ ((unsigned)&CM1CON0*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	C1CH                : 2;
        unsigned	C1R                 : 1;
        unsigned	                    : 1;
        unsigned	C1POL               : 1;
        unsigned	C1OE                : 1;
        unsigned	C1OUT               : 1;
        unsigned	C1ON                : 1;
    };
    struct {
        unsigned	C1CH0               : 1;
        unsigned	C1CH1               : 1;
    };
} CM1CON0bits @ 0x01A;
#endif

// Register: CM2CON0
volatile unsigned char           CM2CON0             @ 0x01B;
// bit and bitfield definitions
volatile bit C2R                 @ ((unsigned)&CM2CON0*8)+2;
volatile bit C2POL               @ ((unsigned)&CM2CON0*8)+4;
volatile bit C2OE                @ ((unsigned)&CM2CON0*8)+5;
volatile bit C2OUT               @ ((unsigned)&CM2CON0*8)+6;
volatile bit C2ON                @ ((unsigned)&CM2CON0*8)+7;
volatile bit C2CH0               @ ((unsigned)&CM2CON0*8)+0;
volatile bit C2CH1               @ ((unsigned)&CM2CON0*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	C2CH                : 2;
        unsigned	C2R                 : 1;
        unsigned	                    : 1;
        unsigned	C2POL               : 1;
        unsigned	C2OE                : 1;
        unsigned	C2OUT               : 1;
        unsigned	C2ON                : 1;
    };
    struct {
        unsigned	C2CH0               : 1;
        unsigned	C2CH1               : 1;
    };
} CM2CON0bits @ 0x01B;
#endif

// Register: CM2CON1
volatile unsigned char           CM2CON1             @ 0x01C;
// bit and bitfield definitions
volatile bit C2SYNC              @ ((unsigned)&CM2CON1*8)+0;
volatile bit T1GSS               @ ((unsigned)&CM2CON1*8)+1;
volatile bit C2HYS               @ ((unsigned)&CM2CON1*8)+2;
volatile bit C1HYS               @ ((unsigned)&CM2CON1*8)+3;
volatile bit T1ACS               @ ((unsigned)&CM2CON1*8)+4;
volatile bit MC2OUT              @ ((unsigned)&CM2CON1*8)+6;
volatile bit MC1ON               @ ((unsigned)&CM2CON1*8)+7;
volatile bit MC1OUT              @ ((unsigned)&CM2CON1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	C2SYNC              : 1;
        unsigned	T1GSS               : 1;
        unsigned	C2HYS               : 1;
        unsigned	C1HYS               : 1;
        unsigned	T1ACS               : 1;
        unsigned	                    : 1;
        unsigned	MC2OUT              : 1;
        unsigned	MC1ON               : 1;
    };
    struct {
        unsigned	: 7;
        unsigned	MC1OUT              : 1;
    };
} CM2CON1bits @ 0x01C;
#endif

// Register: ADRESH
volatile unsigned char           ADRESH              @ 0x01E;
// bit and bitfield definitions

// Register: ADCON0
volatile unsigned char           ADCON0              @ 0x01F;
// bit and bitfield definitions
volatile bit ADON                @ ((unsigned)&ADCON0*8)+0;
volatile bit GO_nDONE            @ ((unsigned)&ADCON0*8)+1;
volatile bit VCFG                @ ((unsigned)&ADCON0*8)+6;
volatile bit ADFM                @ ((unsigned)&ADCON0*8)+7;
volatile bit GO                  @ ((unsigned)&ADCON0*8)+1;
volatile bit CHS0                @ ((unsigned)&ADCON0*8)+2;
volatile bit CHS1                @ ((unsigned)&ADCON0*8)+3;
volatile bit CHS2                @ ((unsigned)&ADCON0*8)+4;
volatile bit CHS3                @ ((unsigned)&ADCON0*8)+5;
volatile bit nDONE               @ ((unsigned)&ADCON0*8)+1;
volatile bit GO_DONE             @ ((unsigned)&ADCON0*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADON                : 1;
        unsigned	GO_nDONE            : 1;
        unsigned	CHS                 : 4;
        unsigned	VCFG                : 1;
        unsigned	ADFM                : 1;
    };
    struct {
        unsigned	: 1;
        unsigned	: 1;
        unsigned	: 4;
        unsigned	: 1;
        unsigned	: 1;
    };
    struct {
        unsigned	                    : 1;
        unsigned	GO                  : 1;
        unsigned	CHS0                : 1;
        unsigned	CHS1                : 1;
        unsigned	CHS2                : 1;
        unsigned	CHS3                : 1;
    };
    struct {
        unsigned	: 1;
        unsigned	nDONE               : 1;
    };
    struct {
        unsigned	: 1;
        unsigned	GO_DONE             : 1;
    };
} ADCON0bits @ 0x01F;
#endif

//
// Special function register definitions: Bank 1
//


// Register: OPTION_REG
volatile unsigned char           OPTION_REG          @ 0x081;
// bit and bitfield definitions
volatile bit PSA                 @ ((unsigned)&OPTION_REG*8)+3;
volatile bit T0SE                @ ((unsigned)&OPTION_REG*8)+4;
volatile bit T0CS                @ ((unsigned)&OPTION_REG*8)+5;
volatile bit INTEDG              @ ((unsigned)&OPTION_REG*8)+6;
volatile bit nRAPU               @ ((unsigned)&OPTION_REG*8)+7;
volatile bit PS0                 @ ((unsigned)&OPTION_REG*8)+0;
volatile bit PS1                 @ ((unsigned)&OPTION_REG*8)+1;
volatile bit PS2                 @ ((unsigned)&OPTION_REG*8)+2;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PS                  : 3;
        unsigned	PSA                 : 1;
        unsigned	T0SE                : 1;
        unsigned	T0CS                : 1;
        unsigned	INTEDG              : 1;
        unsigned	nRAPU               : 1;
    };
    struct {
        unsigned	PS0                 : 1;
        unsigned	PS1                 : 1;
        unsigned	PS2                 : 1;
    };
} OPTION_REGbits @ 0x081;
#endif

// Register: TRISA
volatile unsigned char           TRISA               @ 0x085;
// bit and bitfield definitions
volatile bit TRISA0              @ ((unsigned)&TRISA*8)+0;
volatile bit TRISA1              @ ((unsigned)&TRISA*8)+1;
volatile bit TRISA2              @ ((unsigned)&TRISA*8)+2;
volatile bit TRISA3              @ ((unsigned)&TRISA*8)+3;
volatile bit TRISA4              @ ((unsigned)&TRISA*8)+4;
volatile bit TRISA5              @ ((unsigned)&TRISA*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISA0              : 1;
        unsigned	TRISA1              : 1;
        unsigned	TRISA2              : 1;
        unsigned	TRISA3              : 1;
        unsigned	TRISA4              : 1;
        unsigned	TRISA5              : 1;
    };
} TRISAbits @ 0x085;
#endif

// Register: TRISC
volatile unsigned char           TRISC               @ 0x087;
// bit and bitfield definitions
volatile bit TRISC0              @ ((unsigned)&TRISC*8)+0;
volatile bit TRISC1              @ ((unsigned)&TRISC*8)+1;
volatile bit TRISC2              @ ((unsigned)&TRISC*8)+2;
volatile bit TRISC3              @ ((unsigned)&TRISC*8)+3;
volatile bit TRISC4              @ ((unsigned)&TRISC*8)+4;
volatile bit TRISC5              @ ((unsigned)&TRISC*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISC0              : 1;
        unsigned	TRISC1              : 1;
        unsigned	TRISC2              : 1;
        unsigned	TRISC3              : 1;
        unsigned	TRISC4              : 1;
        unsigned	TRISC5              : 1;
    };
} TRISCbits @ 0x087;
#endif

// Register: PIE1
volatile unsigned char           PIE1                @ 0x08C;
// bit and bitfield definitions
volatile bit TMR1IE              @ ((unsigned)&PIE1*8)+0;
volatile bit TMR2IE              @ ((unsigned)&PIE1*8)+1;
volatile bit C1IE                @ ((unsigned)&PIE1*8)+3;
volatile bit C2IE                @ ((unsigned)&PIE1*8)+4;
volatile bit ECCPIE              @ ((unsigned)&PIE1*8)+5;
volatile bit ADIE                @ ((unsigned)&PIE1*8)+6;
volatile bit T1IE                @ ((unsigned)&PIE1*8)+0;
volatile bit T2IE                @ ((unsigned)&PIE1*8)+1;
volatile bit CCP1IE              @ ((unsigned)&PIE1*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR1IE              : 1;
        unsigned	TMR2IE              : 1;
        unsigned	                    : 1;
        unsigned	C1IE                : 1;
        unsigned	C2IE                : 1;
        unsigned	ECCPIE              : 1;
        unsigned	ADIE                : 1;
    };
    struct {
        unsigned	T1IE                : 1;
        unsigned	T2IE                : 1;
        unsigned	: 3;
        unsigned	CCP1IE              : 1;
    };
} PIE1bits @ 0x08C;
#endif

// Register: PCON
volatile unsigned char           PCON                @ 0x08E;
// bit and bitfield definitions
volatile bit nBOR                @ ((unsigned)&PCON*8)+0;
volatile bit nPOR                @ ((unsigned)&PCON*8)+1;
volatile bit nBOD                @ ((unsigned)&PCON*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	nBOR                : 1;
        unsigned	nPOR                : 1;
    };
    struct {
        unsigned	nBOD                : 1;
    };
} PCONbits @ 0x08E;
#endif

// Register: OSCTUNE
volatile unsigned char           OSCTUNE             @ 0x090;
// bit and bitfield definitions
volatile bit TUN0                @ ((unsigned)&OSCTUNE*8)+0;
volatile bit TUN1                @ ((unsigned)&OSCTUNE*8)+1;
volatile bit TUN2                @ ((unsigned)&OSCTUNE*8)+2;
volatile bit TUN3                @ ((unsigned)&OSCTUNE*8)+3;
volatile bit TUN4                @ ((unsigned)&OSCTUNE*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TUN                 : 5;
    };
    struct {
        unsigned	TUN0                : 1;
        unsigned	TUN1                : 1;
        unsigned	TUN2                : 1;
        unsigned	TUN3                : 1;
        unsigned	TUN4                : 1;
    };
} OSCTUNEbits @ 0x090;
#endif

// Register: ANSEL
volatile unsigned char           ANSEL               @ 0x091;
// bit and bitfield definitions
volatile bit ANS0                @ ((unsigned)&ANSEL*8)+0;
volatile bit ANS1                @ ((unsigned)&ANSEL*8)+1;
volatile bit ANS2                @ ((unsigned)&ANSEL*8)+2;
volatile bit ANS3                @ ((unsigned)&ANSEL*8)+3;
volatile bit ANS4                @ ((unsigned)&ANSEL*8)+4;
volatile bit ANS5                @ ((unsigned)&ANSEL*8)+5;
volatile bit ANS6                @ ((unsigned)&ANSEL*8)+6;
volatile bit ANS7                @ ((unsigned)&ANSEL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ANS0                : 1;
        unsigned	ANS1                : 1;
        unsigned	ANS2                : 1;
        unsigned	ANS3                : 1;
        unsigned	ANS4                : 1;
        unsigned	ANS5                : 1;
        unsigned	ANS6                : 1;
        unsigned	ANS7                : 1;
    };
} ANSELbits @ 0x091;
#endif

// Register: PR2
volatile unsigned char           PR2                 @ 0x092;
// bit and bitfield definitions

// Register: WPUA
volatile unsigned char           WPUA                @ 0x095;
volatile unsigned char           WPU                 @ 0x095;
// bit and bitfield definitions
volatile bit WPUA0               @ ((unsigned)&WPUA*8)+0;
volatile bit WPUA1               @ ((unsigned)&WPUA*8)+1;
volatile bit WPUA2               @ ((unsigned)&WPUA*8)+2;
volatile bit WPUA4               @ ((unsigned)&WPUA*8)+4;
volatile bit WPUA5               @ ((unsigned)&WPUA*8)+5;
volatile bit WPU0                @ ((unsigned)&WPUA*8)+0;
volatile bit WPU1                @ ((unsigned)&WPUA*8)+1;
volatile bit WPU2                @ ((unsigned)&WPUA*8)+2;
volatile bit WPU4                @ ((unsigned)&WPUA*8)+4;
volatile bit WPU5                @ ((unsigned)&WPUA*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUA0               : 1;
        unsigned	WPUA1               : 1;
        unsigned	WPUA2               : 1;
        unsigned	                    : 1;
        unsigned	WPUA4               : 1;
        unsigned	WPUA5               : 1;
    };
    struct {
        unsigned	WPU0                : 1;
        unsigned	WPU1                : 1;
        unsigned	WPU2                : 1;
        unsigned	: 1;
        unsigned	WPU4                : 1;
        unsigned	WPU5                : 1;
    };
} WPUAbits @ 0x095;
#endif

// Register: IOCA
volatile unsigned char           IOCA                @ 0x096;
volatile unsigned char           IOC                 @ 0x096;
// bit and bitfield definitions
volatile bit IOCA0               @ ((unsigned)&IOCA*8)+0;
volatile bit IOCA1               @ ((unsigned)&IOCA*8)+1;
volatile bit IOCA2               @ ((unsigned)&IOCA*8)+2;
volatile bit IOCA3               @ ((unsigned)&IOCA*8)+3;
volatile bit IOCA4               @ ((unsigned)&IOCA*8)+4;
volatile bit IOCA5               @ ((unsigned)&IOCA*8)+5;
volatile bit IOC0                @ ((unsigned)&IOCA*8)+0;
volatile bit IOC1                @ ((unsigned)&IOCA*8)+1;
volatile bit IOC2                @ ((unsigned)&IOCA*8)+2;
volatile bit IOC3                @ ((unsigned)&IOCA*8)+3;
volatile bit IOC4                @ ((unsigned)&IOCA*8)+4;
volatile bit IOC5                @ ((unsigned)&IOCA*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	IOCA0               : 1;
        unsigned	IOCA1               : 1;
        unsigned	IOCA2               : 1;
        unsigned	IOCA3               : 1;
        unsigned	IOCA4               : 1;
        unsigned	IOCA5               : 1;
    };
    struct {
        unsigned	IOC0                : 1;
        unsigned	IOC1                : 1;
        unsigned	IOC2                : 1;
        unsigned	IOC3                : 1;
        unsigned	IOC4                : 1;
        unsigned	IOC5                : 1;
    };
} IOCAbits @ 0x096;
#endif

// Register: SRCON0
volatile unsigned char           SRCON0              @ 0x099;
volatile unsigned char           SRCON               @ 0x099;
// bit and bitfield definitions
volatile bit SRCLKEN             @ ((unsigned)&SRCON0*8)+0;
volatile bit PULSR               @ ((unsigned)&SRCON0*8)+2;
volatile bit PULSS               @ ((unsigned)&SRCON0*8)+3;
volatile bit C2REN               @ ((unsigned)&SRCON0*8)+4;
volatile bit C1SEN               @ ((unsigned)&SRCON0*8)+5;
volatile bit SR0                 @ ((unsigned)&SRCON0*8)+6;
volatile bit SR1                 @ ((unsigned)&SRCON0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SRCLKEN             : 1;
        unsigned	                    : 1;
        unsigned	PULSR               : 1;
        unsigned	PULSS               : 1;
        unsigned	C2REN               : 1;
        unsigned	C1SEN               : 1;
        unsigned	SR                  : 2;
    };
    struct {
        unsigned	: 6;
        unsigned	SR0                 : 1;
        unsigned	SR1                 : 1;
    };
} SRCON0bits @ 0x099;
#endif

// Register: SRCON1
volatile unsigned char           SRCON1              @ 0x09A;
// bit and bitfield definitions
volatile bit SRCS0               @ ((unsigned)&SRCON1*8)+6;
volatile bit SRCS1               @ ((unsigned)&SRCON1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 6;
        unsigned	SRCS                : 2;
    };
    struct {
        unsigned	: 6;
        unsigned	SRCS0               : 1;
        unsigned	SRCS1               : 1;
    };
} SRCON1bits @ 0x09A;
#endif

// Register: ADRESL
volatile unsigned char           ADRESL              @ 0x09E;
// bit and bitfield definitions

// Register: ADCON1
volatile unsigned char           ADCON1              @ 0x09F;
// bit and bitfield definitions
volatile bit ADCS0               @ ((unsigned)&ADCON1*8)+4;
volatile bit ADCS1               @ ((unsigned)&ADCON1*8)+5;
volatile bit ADCS2               @ ((unsigned)&ADCON1*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 4;
        unsigned	ADCS                : 3;
    };
    struct {
        unsigned	: 4;
        unsigned	ADCS0               : 1;
        unsigned	ADCS1               : 1;
        unsigned	ADCS2               : 1;
    };
} ADCON1bits @ 0x09F;
#endif

#endif
