#include "speed_controller.h"

#include "app_config.h"

static int32_t last_speed_error;

void speed_controller_init(void)
{
    last_speed_error = 0;
}

uint8_t speed_controller_calculate_duty(
    uint16_t requested_speed_rpm,
    uint16_t measured_speed_rpm)
{
    uint32_t duty;

    last_speed_error =
        (int32_t)requested_speed_rpm - (int32_t)measured_speed_rpm;

    if (last_speed_error <= 0) {
        return 0U;
    }

    if (last_speed_error >= APP_MAX_ALLOWED_SPEED_ERROR_RPM) {
        return 100U;
    }

    duty = ((uint32_t)last_speed_error * UINT32_C(100)) /
           APP_MAX_ALLOWED_SPEED_ERROR_RPM;
    return (uint8_t)duty;
}

int32_t speed_controller_get_last_error(void)
{
    return last_speed_error;
}
