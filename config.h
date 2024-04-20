/*config.h*/


//Navigate buttons
#define BTN_UP      3                 // Up Button
#define BTN_DOWN    1                 // Down Button
#define BTN_ESC     13                // Exit Button
#define BTN_SEL     5               // Select button
// Comment the following to disable internal pullup for Navigate buttons
#define NAV_BUTTONS_INPUT_PULLUP

#define LARGE_FONT u8g2_font_6x13_mf

#define rxPin D3                         // Приемник Receiver
#define txPin D2                        // Передатчик Transmitter
#define tx2Pin D8                          // Передатчик Transmitter #2

#define repeatSSID "Repeater" // SSID repeater name
#define repeatPASS "12345678" // Pass sid repeater

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 12, 14, U8X8_PIN_NONE); // 12-SCL 14-SDA OLED display pins

#define TOTAL_NAV_BUTTONS 4       // Total Navigation Button used

#define MAX_DEPTH 3

#ifdef LOC
// #define LARGE_FONT
#define INV
#endif
 
 /*Do not change the values(recomended)*/
#ifdef LARGE_FONT
#define menuFont u8g2_font_6x13_mf
#define fontW 5
#define fontH 7
#else
// #define menuFont System5x7
#define menuFont u8g2_font_6x13_mf
#define fontW 5
#define fontH 7
#endif