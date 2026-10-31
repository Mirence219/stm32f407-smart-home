#include "GuiState.h"

void GuiState::reset_manual_fan()
{
    fan_level = 0;
}

void GuiState::reset_manual_lights()
{
    for (uint8_t i = 0; i < 4; ++i)
    {
        led_enabled[i] = false;
    }
}

void GuiState::home()
{
    page_state = 0;
    focus_index = 0;
}

void GuiState::tab()
{
    if (focus_index >= max_index)
    {
        focus_index = 0;
    }
    else
    {
        ++focus_index;
    }
}

//状态机配置
void GuiState::back()
{
    if (page_state != 0)
    {
        page_state = 0;
        focus_index = 0;
    }
}

void GuiState::select()
{
    if (page_state == 0)
    {
        if (focus_index <= 2)
        {
            page_state = static_cast<uint8_t>(focus_index + 1);
        }
        focus_index = 0;
        return;
    }

    if (page_state == 2)
    {
        if (focus_index == 0)
        {
            lock_enabled = !lock_enabled;
        }
        else if (focus_index == 1)
        {
            if (!auto_cooling_enabled)
            {
                fan_level = static_cast<uint8_t>((fan_level + 1) % 4);
            }
        }
        else if (focus_index >= 2 && focus_index <= 5 && !auto_lighting_enabled)
        {
            const uint8_t led_index = static_cast<uint8_t>(focus_index - 2);
            led_enabled[led_index] = !led_enabled[led_index];
        }
    }
    else if (page_state == 3)
    {
        if (focus_index == 0)
        {
            auto_cooling_enabled = !auto_cooling_enabled;
            if (auto_cooling_enabled)
            {
                reset_manual_fan();
            }
        }
        else if (focus_index == 1)
        {
            auto_lighting_enabled = !auto_lighting_enabled;
            if (auto_lighting_enabled)
            {
                reset_manual_lights();
            }
        }
    }
}

GuiState::GuiState()
    : page_state(0), focus_index(0), max_index(0),
      lock_enabled(false), fan_level(0),
      auto_cooling_enabled(false), auto_lighting_enabled(false)
{
    reset_manual_lights();
}

void GuiState::handle_input_signal(GuiInputSignal signal)
{
    switch (signal)
    {
        case GuiInputSignal::HOME: home(); break;
        case GuiInputSignal::TAB: tab(); break;
        case GuiInputSignal::BACK: back(); break;
        case GuiInputSignal::SELECT: select(); break;
    }
}

void GuiState::set_max_index(uint16_t index)
{
    max_index = index;
    normalize_focus_index();
}

void GuiState::set_focus_index(uint16_t index)
{
    focus_index = index;
    normalize_focus_index();
}

void GuiState::normalize_focus_index()
{
    if (focus_index > max_index)
    {
        focus_index = 0;
    }
}

uint8_t GuiState::get_page_state() const
{
    return page_state;
}

uint16_t GuiState::get_focus_index() const
{
    return focus_index;
}

bool GuiState::get_lock_enabled() const
{
    return lock_enabled;
}

uint8_t GuiState::get_fan_level() const
{
    return fan_level;
}

bool GuiState::get_led_enabled(uint8_t index) const
{
    return index < 4 ? led_enabled[index] : false;
}

bool GuiState::get_auto_cooling_enabled() const
{
    return auto_cooling_enabled;
}

bool GuiState::get_auto_lighting_enabled() const
{
    return auto_lighting_enabled;
}
