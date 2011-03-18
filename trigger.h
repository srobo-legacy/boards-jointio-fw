#ifndef __TRIGGER_H
#define __TRIGGER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
	TRIG_OP_LESS,
	TRIG_OP_GREATER
} trigger_op_t;

void trigger_init(void);

/* Enable/disable trigger on a given pin */
void trigger_set_en(uint8_t index, bool en);
bool trigger_get_en(uint8_t index);

/* Sets the threshold for the trigger on a given pin */
void trigger_set_thresh(uint8_t index, uint16_t thresh);
uint16_t trigger_get_thresh(uint8_t index);

/* Sets the condition to be satisfied for the trigger to occur */
void trigger_set_op(uint8_t index, trigger_op_t op);
trigger_op_t trigger_get_op(uint8_t index);

/* Checks the inputs against any enabled triggers and returns a bit-field
 * of the inputs which have been triggered */
uint8_t trigger_check(void);

#endif /* __TRIGGER_H */
