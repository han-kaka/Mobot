#include "bsp_motor.h"

void motor_init(void)
{
    gpio_init_t x;

    x.mode = GPIO_MODE_OUTPUT;
    x.odos = GPIO_PUSH_PULL;
    x.pupd = GPIO_PUSH_UP;
    x.odrv = GPIO_OUT_DRIVE_NORMAL;
    x.flt  = GPIO_FILTER_DISABLE;
    x.type = GPIO_TYPE_CMOS;
    x.func = GPIO_FUNC_1;

    ald_gpio_init(MOTOR_CTR_PORT, MOTOR_CTR_PIN, &x);
    ald_gpio_write_pin(MOTOR_CTR_PORT, MOTOR_CTR_PIN, 0);
}

