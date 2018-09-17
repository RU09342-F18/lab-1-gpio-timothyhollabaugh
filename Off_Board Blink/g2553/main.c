
#include <msp430.h>

#define LED1_PIN 0
#define LED2_PIN 6
#define BUTTON_PIN 3

char led1_pattern[24] = {1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0};
char led2_pattern[24] = {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0};

void setup_watchdog() {
    WDTCTL = WDTPW | WDTHOLD;
}

void setup_led() {
    P1DIR |= 1<<LED1_PIN;
    P1OUT &= ~(1<<LED2_PIN);

    P1DIR |= 1<<LED2_PIN;
    P1OUT &= ~(1<<LED2_PIN);

    P1DIR &= ~(1<<BUTTON_PIN);
}

void setup_button() {
    P1DIR &= ~(1<<BUTTON_PIN);
}

int main() {
    setup_watchdog();
    setup_led();
    setup_button();

    int pattern_index = 0;
    while(1) {

        if (P1IN & (1<<BUTTON_PIN)) {
            if (led1_pattern[pattern_index]) {
                P1OUT |= 1 << LED1_PIN;
            } else {
                P1OUT &= ~(1 << LED1_PIN);
            }
            P1OUT &= ~(1 << LED2_PIN);
        } else {

            if (led2_pattern[pattern_index]) {
                P1OUT |= 1 << LED2_PIN;
            } else {
                P1OUT &= ~(1 << LED2_PIN);
            }
            P1OUT &= ~(1 << LED1_PIN);
        }

        if (pattern_index < 23) {
            pattern_index++;
        } else {
            pattern_index = 0;
        }

        for (long i = 1000L; i; i--) {
            __no_operation();
        }
    }
}

