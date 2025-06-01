# STM32 barebones approach
A I2C MPU6050 implementation for the STM32F103C6T6 using the HAL library; however this would work with any STM32F1xx chip 

## Parts Used
- STM32F103C6T6 for sections 1 & 2
- STM32F411RE Nucleo board for rest
- Logic Analyzer (used to see the communications)
- [Realterm](https://sourceforge.net/projects/realterm/) for UART communication
- Potentiometer (or any ADC device)
- MPU6050 (I2C) device
- GMT020-02 display with ST7789 display driver (SPI device)


## Alternative barebones CMSIS standard
[I2C driver](https://github.com/Sparrowehawk/STM32_barebones/tree/main/section_9%20-%20I2C)

## Section discreptions

### Section 1 - Direct address configuration
Accessing and toggling an LED by manually writing each address and using structs to aide.

### Section 2 - GPIO
Example of using the BSRR (Bit Set Reset Reg) and input to toggle an LED.

### Section 3 - UART
Communicate to and fro a computer via UART.

### Section 4 - ADC
Setting and intiialisng a ADC.

### Section 5 - Systick timer
Configuring the Systick timer register to give a 1 second delay.

### Section 6 - Timers
Using the onboard clock to generate a time signal to use.

### Section 7 - Interrupts
Redo sections 3 - 6 via the ISR instead.

### Section 8 - DMA
Using DMA1 Stream 6 to write directly into the register.

### Section 9 - I2C
Configure and initialise a MPU6050 via I2C.

### Section 10 - SPI
Configure and initialise a GMT020-02 TFT display via SPI.

---

## License
MIT License

---

## Credit
This repo was made following a course by [Isreal Gbati](https://www.udemy.com/course/embedded-systems-bare-metal-programming/)

---

## Author
[Sparrowehawk](https://github.com/Sparrowehawk)
