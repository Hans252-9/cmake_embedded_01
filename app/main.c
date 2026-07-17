#include "motor_controller.h"

int main(void)
{
    motor_controller_init();

    for (;;) {
        motor_controller_update();
    }
}
