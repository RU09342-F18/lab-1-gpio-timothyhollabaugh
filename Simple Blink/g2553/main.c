
#include <msp430.h>

#define LED_PIN 0

void setup_watchdog() {
    WDTCTL = WDTPW | WDTHOLD;
}

void setup_led() {
    P1DIR |= 1<<LED_PIN;
    P1OUT &= ~(1<<LED_PIN);
}

int main() {
    setup_watchdog();
    setup_led();

    while(1) {
        P1OUT ^= 1<<LED_PIN;
        for (long i = 50000L; i; i--) {
            __no_operation();
        }
    }
}

