#ifndef SPEED_CONTROLLER_H
#define SPEED_CONTROLLER_H

#include <stdint.h>

void speed_controller_init(void);
uint8_t speed_controller_calculate_duty(
    uint16_t requested_speed_rpm,
    uint16_t measured_speed_rpm);
int32_t speed_controller_get_last_error(void);

#endif
