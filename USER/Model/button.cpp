#include "button.h"
#include "delay.h"

Button::Button(ModelType model_type, GPIO_TypeDef* port, uint16_t pin, uint8_t active_level)
	: model_data(model_type), port(port), pin(pin), active_level(active_level),
	  last_raw_state(1), initialized(false)
{
}

bool Button::init()
{
	Key_InitPin(port, pin, active_level);
	last_raw_state = Key_ReadPin(port, pin);
	initialized = true;
	set_enabled(last_raw_state == active_level);
	return model_data.set(ModelData::DataName::READY, false);
}

void Button::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IFunctionalModel*>(this), mode);
}

void Button::set_model_data(const ModelData& data)
{
	if (data.get_model_type() == model_data.get_model_type())
	{
		model_data = data;
	}
}

void Button::set_enabled(bool enabled)
{
	bool previous_enabled = false;
	if (model_data.get(ModelData::DataName::ENABLE, previous_enabled) &&
		previous_enabled != enabled)
	{
		model_data.set(ModelData::DataName::ENABLE, enabled);
	}
}

void Button::update()
{
	if (!initialized)
	{
		return;
	}

	model_data.set(ModelData::DataName::READY, false);
	const uint8_t raw_state = Key_ReadPin(port, pin);
	if (raw_state != last_raw_state)
	{
		Delay_ms(10);
		last_raw_state = Key_ReadPin(port, pin);
	}

	set_enabled(last_raw_state == active_level);
}
