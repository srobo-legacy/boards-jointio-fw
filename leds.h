#ifndef __LEDS_H
#define __LEDS_H

/* Debugging and SRIC activity LED next to MSP */
#define LED_DBG_OUT P3OUT
#define LED_DBG (1<<1)

#define leds_init() do { P3OUT &= ~LED_DBG; P3DIR |= LED_DBG; } while(0)

#define __led_set(led_out, led, x) do { if (x) led_out |= led; \
                                        else   led_out &= ~led; } while(0)

#define __led_toggle(led_out, led) do { led_out ^= led; } while(0)

#define dbg_set(x)       __led_set(LED_DBG_OUT, LED_DBG, x)
#define dbg_toggle()     __led_toggle(LED_DBG_OUT, LED_DBG)

#endif /* __LEDS_H */
