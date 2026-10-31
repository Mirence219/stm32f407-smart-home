#include "application.h"
#include "led_gpio.h"
#include "gui.h"
#include "delay.h"

static Application app;

int main()
{
    Delay_Init();

    LED_InitPin(GPIOF, GPIO_Pin_9);
    LED_WritePin(GPIOF, GPIO_Pin_9, 1);

    const ApplicationInitError error = app.init();
    if (error == ApplicationInitError::NONE)
    {
        app.run();
    }
}