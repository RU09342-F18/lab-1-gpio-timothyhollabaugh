
#include <msp430.h>

#define LED1_PIN 0
#define LED2_PIN 7

char led1_pattern[24] = {1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0};
char led2_pattern[24] = {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0};

void setup_watchdog() {
    WDTCTL = WDTPW | WDTHOLD;
}

void setup_led() {
    P1DIR |= 1<<LED1_PIN;
    P1OUT &= ~(1<<LED2_PIN);

    P4DIR |= 1<<LED2_PIN;
    P4OUT &= ~(1<<LED2_PIN);
}

int main() {
    setup_watchdog();
    setup_led();

    int pattern_index = 0;
    while(1) {

        if (led1_pattern[pattern_index]) {
            P1OUT |= 1 << LED1_PIN;
        } else {
            P1OUT &= ~(1 << LED1_PIN);
        }

        if (led2_pattern[pattern_index]) {
            P4OUT |= 1 << LED2_PIN;
        } else {
            P4OUT &= ~(1 << LED2_PIN);
        }

        if (pattern_index < 23) {
            pattern_index++;
        } else {
            pattern_index = 0;
        }

        for (long i = 10000L; i; i--) {
            __no_operation();
        }
    }
}

