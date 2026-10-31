#ifndef FANS_H
#define FANS_H

#include "stm32f4xx.h"
#include "i_output_model.h"
#include "model_data.h"

class Fan : public IOutputModel {
private:
    ModelData model_data{ModelType::FAN};
    GPIO_TypeDef *port;
    uint16_t pin;
    void apply_speed(float speed);
public:
    Fan(GPIO_TypeDef *port, uint16_t pin);
    bool init() override;
    void accept(IVisitor* visitor, ModelDataMode mode) override;
    ModelData& get_model_data() override { return model_data; }
    void set_model_data(const ModelData& data) override;
};

#endif
