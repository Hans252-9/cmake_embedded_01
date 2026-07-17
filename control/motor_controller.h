#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <stdbool.h>
#include <stdint.h>

void motor_controller_init(void);
void motor_controller_update(void);
uint8_t motor_controller_calculate_temperature_duty(int16_t temperature_c);
bool motor_controller_has_overtemperature(void);
bool motor_controller_has_overcurrent(void);
uint8_t motor_controller_get_commanded_duty(void);

#endif
