typedef unsigned char uint8_t;

#define DDRB *((volatile uint8_t *) 0x24) // port B Data direction Register
#define PORTB *((volatile uint8_t *) 0x25) // Port B Data Register

/*
 * we'll be using timer_1 for this project, which has 3 control, 4 data registers and 2 interrupt registers.
 * control registers: TCCR1A, TCCR1B, TCCR1C
 * data registers: OCR1A, OCR1B, TCNT1, ICR1
 * interrupt registers: TIMSK1, TIFR1
 */

//define timer_1 control register, A and B
#define TCCR1A *((volatile uint8_t *) 0x80) // Timer/Counter1 Control Register A
#define TCCR1B *((volatile uint8_t *) 0x81) // Timer/Counter1 Control Register B

// # TCNT1
#define TCNT1H *((volatile uint8_t *) 0x85)
#define TCNT1L *((volatile uint8_t *) 0x84)
#define TCNT1 *((volatile uint8_t *)0x84) 
//Timer1 16-bit control register: counts 0-65535
// this timer 1 is split into two 8-bit registers: TCNT1H(higher byte) and TCNT1L(lower byte)

// Output Compare Registers for Timer/Counter1
#define OCR1AH *((volatile uint8_t *) 0x89)
#define OCR1AL *((volatile uint8_t *) 0x88)

#define ICR1H *((volatile uint8_t *) 0x87)
#define ICR1L *((volatile uint8_t *) 0x86)
#define TIMSK1 *((volatile uint8_t *) 0x6F)
#define TIFR1 *((volatile uint8_t *) 0x36)



#define TIMER1_COUNT 62499
#define PORTB5 5
#define DDRB5 5
#define CS12 2 //to set the prescaler to 256, CS12 = 1, CS11 = 0, CS10 = 0 in TCCR1B
#define WGM12 3 //to set the mode to CTC, WGM12 = 1, WGM11 = 0, WGM10 = 0 in TCCR1B
#define TOV1 0  //Timer1 Overflow Flag in TIFR1
#define OCIE1A 1 //Timer1 Output Compare A Match Interrupt Enable in TIMSK1
#define OCF1A 1     //Output Compare A match flag in TIFR1


//defining a Interupt Service Routine(ISR) for timer1 interrupt
void __vector_11(void) __attribute__((signal, used, externally_visible));

void __vector_11(void)
{
    PORTB ^= (1 << PORTB5); // Toggle PORTB5
}

void enable_interrupts() {
    __asm__ __volatile__("sei" ::: "memory");
    //this line is to add assembly code that sets Global Interrupt Enable in Status Register(SREG).
}

void disable_interrupts() {
    __asm__ __volatile__("cli" ::: "memory");
    //this line is to add assembly code that clears the  Global Interrupt Enable in Status Register(SREG).
}

void sleep() {
    __asm__ __volatile__("sleep" ::: "memory");
}


int main(void) {
    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B = 0;

    // set timer1 compare register high byte and lower byte
    // by splitting the value
    OCR1AH = TIMER1_COUNT >> 8;
    OCR1AL = TIMER1_COUNT & 0xFF;

    TCCR1B |= ((1 << CS12) | (1 << WGM12)); // Set Timer1 Clock Prescaler to 256
    TIFR1 ^= (1 << OCF1A); // Clear Timer1 Compare Match A Flag
    DDRB |= (1 << DDRB5); // Set PORTB5 as output (Pin 13 on Arduino Uno)

    disable_interrupts();

    TIMSK1 = (1 << OCIE1A); // Enable Timer1 Overflow Interrupt

    enable_interrupts();

    PORTB |= (1 << PORTB5); // Set PORTB5 to High

    while (1) {
        sleep();
    }
}
