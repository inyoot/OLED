/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>

volatile uint32_t g_ul_ms_ticks = 0;
#define BLINK_PERIOD        1000

void SysTick_Handler(void)
{
	g_ul_ms_ticks++;
	printf("%d\r",g_ul_ms_ticks);
}

/**
 * \brief Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
};

	/* Configure console UART. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}


int main (void)
{
	board_init();
	sysclk_init();
	configure_console();
	
	/* Configure systick for 1 ms */
	puts("Configure system tick to get 1ms tick period.\r");
	if (SysTick_Config(sysclk_get_cpu_hz() / BLINK_PERIOD)) {
		puts("-F- Systick configuration error\r");
		while (1);
	}
	

	// Insert application code here, after the board has been initialized.

	// This skeleton code simply sets the LED to the state of the button.
	while (1) {
		// Is button pressed?
		if (ioport_get_pin_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			// Yes, so turn LED on.
			ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE);
		} else {
			// No, so turn LED off.
			ioport_set_pin_level(LED_0_PIN, !LED_0_ACTIVE);
		}
	}
}
