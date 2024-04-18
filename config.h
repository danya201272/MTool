/*config.h*/


//Navigate buttons
#define BTN_UP      3                 // Up Button
#define BTN_DOWN    1                 // Down Button
#define BTN_ESC     13                // Exit Button
#define BTN_SEL     5               // Select button
// Comment the following to disable internal pullup for Navigate buttons
#define NAV_BUTTONS_INPUT_PULLUP

#define LARGE_FONT u8g2_font_7x13_mf

#define rxPin D3                         // Приемник
#define txPin D8                        // Передатчик

#define TOTAL_NAV_BUTTONS 4       // Total Navigation Button used

#define MAX_DEPTH 3

#ifdef LOC
// #define LARGE_FONT
#define INV
#endif
 
 /*Do not change the values(recomended)*/
#ifdef LARGE_FONT
#define menuFont u8g2_font_7x13_mf
#define fontW 5
#define fontH 8
#else
// #define menuFont System5x7
#define menuFont u8g2_font_7x13_mf
#define fontW 5
#define fontH 8
#endif