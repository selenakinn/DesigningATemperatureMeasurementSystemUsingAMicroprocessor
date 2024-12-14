#include <xc.h>
#define _XTAL_FREQ 20000000  // Microcontroller frequency (20 MHz)

// ADC initialization function
void ADC_init() {
    ADCON1 = 0x0E;  // Set Vdd and Vss as analog reference
    ADCON0 = 0x01;  // Enable the ADC module
}

// ADC reading function
unsigned int read_ADC(unsigned char channel) {
    ADCON0 = (channel << 3) | 0x01;  // Channel selection and enabling the ADC
    __delay_ms(2);  // Short delay for stabilization
    GO_nDONE = 1;  // Start the conversion
    while (GO_nDONE);  // Wait until the conversion is complete
    return ((ADRESH << 8) | ADRESL);  // Return the 10-bit ADC result
}

void main() {
    unsigned int adc_value;
    float temperature;

    ADC_init();  // Initialize the ADC

    while (1) {
        adc_value = read_ADC(0);  // Read temperature from channel 0
        temperature = (adc_value * 5.0 / 1024.0) * 100;  // Convert ADC value to temperature

        // Display the result (e.g., on an LCD or via UART)
        __delay_ms(1000);  // Wait for 1 second
    }
}
