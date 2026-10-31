#ifndef ATTITUDE_SENSOR_H
#define ATTITUDE_SENSOR_H

#include "i_input_model.h"
#include "model_data.h"

class AttitudeSensor : public IInputModel {
private:
    ModelData model_data{ModelType::ATTITUDE_SENSOR};

public:
    bool init() override;
    void accept(IVisitor* visitor, ModelDataMode mode) override;
    ModelData& get_model_data() override { return model_data; }
    void update() override;
};

#endif
