#include <msp430.h> 
#include "lcd.h"
#include "button.h"
#include "clock.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    initSPI();
    LCDinit();
    LCDclear();

    char *topMessage = "ECE382 is my Favorite Class!";
    char *messagePrompt = "Message?";
    char *keyPrompt = "Press123";
    char *message1 = "What is the air-speed of an unladen swallow?";
    char *message2 = "African or European?";
    char *message3 = "Well I don't know that!";
    cursorToLineOne();
    writeString(messagePrompt);
    cursorToLineTwo();
    writeString(keyPrompt);

    configureP1PinAsButton(BIT1|BIT2|BIT3);         // configure pins 1, 2, and 3 as buttons

        P1DIR |= BIT0|BIT6;                             // set launchpad LEDs to output

        while (1) {
            char buttons[] = {BIT1, BIT2, BIT3};
            char pressedButton = pollP1Buttons(buttons, 3);

            switch (pressedButton) {
                case BIT1:
                	waitForP1ButtonRelease(BIT1);
                	scrollString(topMessage, message1);
                    break;
                case BIT2:
                	waitForP1ButtonRelease(BIT2);
                	scrollString(topMessage, message2);
                    break;
                case BIT3:
                    waitForP1ButtonRelease(BIT3);
                    scrollString(topMessage, message3);
                    break;
            }
        }
	return 0;
}
