#include "fans.h"
#include "fan.h"

Fan::Fan(GPIO_TypeDef *port, uint16_t pin)
    : port(port), pin(pin)
{
}

bool Fan::init()
{
	//TIM2_Int_Init(199, 8399);
	return false;
}

void Fan::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IOutputModel*>(this), mode);
}


void Fan::set_model_data(const ModelData& data)
{
	if (data.get_model_type() != model_data.get_model_type())
	{
		return;
	}

	bool old_enabled = false;
	bool new_enabled = false;
	float old_speed = 0.0f;
	float new_speed = 0.0f;
	model_data.get(ModelData::DataName::ENABLE, old_enabled);
	model_data.get(ModelData::DataName::SPEED, old_speed);
	data.get(ModelData::DataName::ENABLE, new_enabled);
	data.get(ModelData::DataName::SPEED, new_speed);
	model_data = data;
	if (old_speed != new_speed)
	{
		apply_speed(new_speed);
	}
}

void Fan::apply_speed(float speed)
{
	if (speed < 0.0f)
	{
		speed = 0.0f;
	}
	else if (speed > 3.0f)
	{
		speed = 3.0f;
	}
	Fan_Handle(static_cast<uint8_t>(speed + 0.5f));
}
