
    disable_interrupts();

    TIMSK1 = (1 << OCIE1A); // Enable Timer1 Overflow Interrupt

    enable_interrupts();

    PORTB |= (1 << PORTB5); // Set PORTB5 to High

    while (1) {
        sleep();
    }
