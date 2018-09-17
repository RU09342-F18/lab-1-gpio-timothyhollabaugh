
// include the msp430 defines
#include <msp430.h>

// define what pins the leds are on
#define LED1_PIN 0
#define LED2_PIN 6

// Define the patterns for each led
// There are 24 steps, which allows each led to blink at seperate
// rates that are not multiples of each other.
char led1_pattern[24] = {1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0};
char led2_pattern[24] = {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0};

void setup_watchdog() {
    // disable the watchdog
    WDTCTL = WDTPW | WDTHOLD;
}

void setup_led() {
    // configure led1 as output
    P1DIR |= 1<<LED1_PIN;
    // and set to off
    P1OUT &= ~(1<<LED2_PIN);

    // configure led2 as output
    P1DIR |= 1<<LED2_PIN;
    // and set to off
    P1OUT &= ~(1<<LED2_PIN);
}

int main() {

    // setup initial registers
    setup_watchdog();
    setup_led();

    // the pattern index
    // used to determine which step of the pattern we are on
    int pattern_index = 0;

    // enter infinite loop
    while(1) {

        // Adjust led1 according to the current step in the pattern
        if (led1_pattern[pattern_index]) {
            P1OUT |= 1 << LED1_PIN;
        } else {
            P1OUT &= ~(1 << LED1_PIN);
        }

        // Adjust led2 according to the current step in the pattern
        if (led2_pattern[pattern_index]) {
            P1OUT |= 1 << LED2_PIN;
        } else {
            P1OUT &= ~(1 << LED2_PIN);
        }

        // increase the pattern index if it is less than 23,
        // reset to 0 otherwise
        if (pattern_index < 23) {
            pattern_index++;
        } else {
            pattern_index = 0;
        }

        // busy wait for timing
        // makes sure people can actually see the led blink
        // the delay is determined by the initial value of i
        for (long i = 10000L; i; i--) {
            __no_operation();
        }
    }
}

