#include "buzzer.h"
#include "beep.h"

Buzzer::Buzzer(GPIO_TypeDef *port, uint16_t pin)
	: port(port), pin(pin)
{
}

bool Buzzer::init()
{
	if (!BEEP_InitPin(port, pin))
	{
		return false;
	}
	BEEP_WritePin(port, pin, 0);
	return true;
}

void Buzzer::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IOutputModel*>(this), mode);
}


void Buzzer::set_model_data(const ModelData& data)
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
		apply_enabled(new_enabled);
	}
}

void Buzzer::apply_enabled(bool enabled)
{
	BEEP_WritePin(port, pin, enabled ? 1 : 0);
}
