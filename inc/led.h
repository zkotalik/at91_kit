#ifndef _LED_H
#define _LED_H
#include <stdint.h>

#define GREEN_LED       (1<<20)
#define YELLOW_LED      (1<<5)
#define RED_LED         (1<<3)

void ledInit(void);
void ledToggle(uint32_t);
void delay_ms(int);
void ledOn(uint32_t);
void ledOff(uint32_t);

#endif /* _LED_H */
