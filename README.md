# ControladorLoRa

## Cambios a heltec_unofficial.h

Cambio de:

```cpp
// SPI pins
#define SS        GPIO_NUM_8
#define MOSI      GPIO_NUM_10
#define MISO      GPIO_NUM_11
#define SCK       GPIO_NUM_9
// Radio pins
#define DIO1      GPIO_NUM_14
#define RST_LoRa  GPIO_NUM_12
#define BUSY_LoRa GPIO_NUM_13
// Display pins
#define SDA_OLED  GPIO_NUM_17
#define SCL_OLED  GPIO_NUM_18
#define RST_OLED  GPIO_NUM_21`
```

a:

```cpp
// SPI pins
//#define SS        GPIO_NUM_8
//#define MOSI      GPIO_NUM_10
//#define MISO      GPIO_NUM_11
//#define SCK       GPIO_NUM_9
// Radio pins
#define DIO1      GPIO_NUM_14
//#define RST_LoRa  GPIO_NUM_12
//#define BUSY_LoRa GPIO_NUM_13
// Display pins
//#define SDA_OLED  GPIO_NUM_17
//#define SCL_OLED  GPIO_NUM_18
//#define RST_OLED  GPIO_NUM_21
```

También es necesario **Cambiar todas las variables globales a static**
