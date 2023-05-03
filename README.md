# pico_rf
RP2040 Adafruit/RadioHead clone for RFMx radios

# Issues
  - Compile [error output]() - SPI config related.
  - Check [clk and osc divisors](https://github.com/dragino/RadioHead/blob/master/RHHardwareSPI.cpp)
  - Defined rp2040 SPI clock divisors and timings
```  
// Master clock frequency
#define VARIANT_MCK     (62500000ul)

// Frequency of the board main oscillator
#define VARIANT_MAINOSC (12000ul)
```
  - Verify constructor RF_ASK() updates default SPI freq and pins.

``` //RP2040 SPI_0 bus see Pins_Arduino.h move to RH_ASK.h 
#define MISO 16
#define MOSI 19
#define SCK 18

RH_ASK(uint16_t speed = 12000000, uint8_t rxPin = 19, uint8_t txPin = 16, uint8_t pttPin = 18, bool pttInverted = false);
