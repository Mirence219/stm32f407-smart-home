#ifndef GUI_STATE_H
#define GUI_STATE_H

#include <stdint.h>

enum class GuiInputSignal : uint8_t {
    BACK,
    SELECT,
    HOME,
    TAB
};

class GuiState {
private:
    uint8_t page_state;
    uint16_t focus_index;
    uint16_t max_index;
    bool lock_enabled;
    uint8_t fan_level;
    bool led_enabled[4];
    bool auto_cooling_enabled;
    bool auto_lighting_enabled;
    void home();
    void tab();
    void back();
    void select();
    void normalize_focus_index();
    void reset_manual_fan();
    void reset_manual_lights();

public:
    GuiState();
    void handle_input_signal(GuiInputSignal signal);
    void set_max_index(uint16_t index);
    void set_focus_index(uint16_t index);
    uint8_t get_page_state() const;
    uint16_t get_focus_index() const;
    bool get_lock_enabled() const;
    uint8_t get_fan_level() const;
    bool get_led_enabled(uint8_t index) const;
    bool get_auto_cooling_enabled() const;
    bool get_auto_lighting_enabled() const;
};

#endif