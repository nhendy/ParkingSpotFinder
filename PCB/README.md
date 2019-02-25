# Pinout

## MCU to CM3

| STM Pins      | CM3 Pins   | Functionality   |
| ------------- | ---------- | --------------- |
| PD_2          | 51          | USART5 RX  -->  GPIO14 TX|
| PC_12         | 53          | USART5 TX  -->  GPIO15 RX|
## MCU to JTAG
| STM Pins      | JTAG Pins    | Functionality   |
| ------------- | ----------   | --------------- |
| PA_13         | 1            | SWDIO  -->  VDD|
| PA_14         | 2            | SWCLK  -->  SWDIO|
| PA_15         | 3,5,9        | JTDI  -->  GND|
| PB_3          | 6            | SWO   -->  SWO|
| PB_4          | 10           | JTRST  -->  RST|

## MCU to Sensor
| STM Pins      | Sensor Pins    | Functionality   |
| ------------- | ----------   | --------------- |
| PF_6         | Pin 5            | RX  -->  Serial out|
| PA_7         | _          | |
## MCU to LCD
| STM Pins      | LCD Pins    | Functionality   |
| ------------- | ----------   | --------------- |
| PB_2         | 3            | QUAD_SPI_SCLK  |
| PE_7         | 5            | QUAD_SPI_IO0  |
| PE_8         | 4            | QUAD_SPI_IO1|
| PE_9         | 11           | QUAD_SPI_IO2|
| PE_10         | 12          | QUAD_SPI_IO3|





