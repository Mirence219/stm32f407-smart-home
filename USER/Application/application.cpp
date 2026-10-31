#include "application.h"
#include "delay.h"

Application::Application(): 
    model(),
    controller(model.get_model_manager()),
    view(model.get_lcd(), controller.get_model_snap_shot(), controller.get_gui_state())
{
}

ApplicationInitError Application::init()
{
    if (!model.init())
    {
        return ApplicationInitError::MODEL_INIT_FAILED;
    }

    return ApplicationInitError::NONE;
}

void Application::run()
{
    while (1) 
    {
        controller.update_models();
        controller.read_model_data();
        controller.execute_logic();
        controller.write_model_data();
        #if DEBUG
        {
            view.show_debug();
        }
        #else
        {
            view.show();
        }
        #endif
    }
}