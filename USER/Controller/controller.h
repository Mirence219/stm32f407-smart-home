#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model_manager.h"
#include "model_snap_shot.h"
#include "model_visitor.h"
#include "GuiState.h"

class Controller {
private:
    ModelSnapShot model_snap_shot;
    ModelVisitor model_visitor;
    GuiState gui_state;

public:
    explicit Controller(ModelManager* model_manager);
    void read_model_data();
    void write_model_data();
    void update_models();
    ModelSnapShot* get_model_snap_shot();
    GuiState* get_gui_state();

    void execute_logic();
    bool check_button_enabled(ModelType button_type);
    void button_logic();
};

#endif
