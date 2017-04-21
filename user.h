/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);                                 /* I/O and Peripheral Initialization */

void initLCD(void);                                 /* LCD 16214 Initialization */
void lcdEnable(void);       

void lcdWriteInt(int num);                          /* Display int number on LCD */
void lcdWriteUI(unsigned int num);                  /* Display unsigned int number on LCD */
void lcdWriteChar(unsigned char leter);             /* Display character on LCD */
void lcdWriteString(unsigned char str[]);           /* Display string on LCD */
void clearDisplay();                                /* Clear display string on LCD */

#define lcd_DB4 PORTDbits.RD0
#define lcd_DB5 PORTDbits.RD1
#define lcd_DB6 PORTDbits.RD2
#define lcd_DB7 PORTDbits.RD3
#define lcd_RS  PORTCbits.RC2
#define lcd_E   PORTCbits.RC5
#define lcd_DB  PORTD

#define _XTAL_FREQ 4000000


void ledOn_0();
void ledOn_1();
void ledOn_2();
void ledOn_3();

void ledOff_0();
void ledOff_1();
void ledOff_2();
void ledOff_3();

