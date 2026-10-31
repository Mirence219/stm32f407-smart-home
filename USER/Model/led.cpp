#include "led.h"

Led::Led(ModelType model_type, GPIO_TypeDef* port, uint16_t pin)
	: model_data(model_type), port(port), pin(pin)
{
}

bool Led::init()
{
	LED_InitPin(port, pin);
	write_output(false);
	return true;
}

void Led::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IOutputModel*>(this), mode);
}


void Led::set_model_data(const ModelData& data)
{
	if (data.get_model_type() != model_data.get_model_type())
	{
		return;
	}

	bool old_enabled = false;
	bool new_enabled = false;
	model_data.get(ModelData::DataName::ENABLE, old_enabled);
	data.get(ModelData::DataName::ENABLE, new_enabled);
	model_data = data;
	if (old_enabled != new_enabled)
	{
		write_output(new_enabled);
	}
}

void Led::write_output(bool enabled)
{
	LED_WritePin(port, pin, enabled ? 1 : 0);
}
