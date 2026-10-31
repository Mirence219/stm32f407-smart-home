#include "steering_gear.h"
#include "SteerGear.h"

bool SteeringGear::init()
{
	SteerGear_Init();
	SteerGear_SetPosition(0);
	return true;
}

void SteeringGear::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IOutputModel*>(this), mode);
}


void SteeringGear::set_model_data(const ModelData& data)
{
	if (data.get_model_type() != model_data.get_model_type())
	{
		return;
	}

	bool old_enabled = false;
	bool new_enabled = false;
	bool old_reserve = false;
	bool new_reserve = false;
	model_data.get(ModelData::DataName::ENABLE, old_enabled);
	model_data.get(ModelData::DataName::RESERVE, old_reserve);
	data.get(ModelData::DataName::ENABLE, new_enabled);
	data.get(ModelData::DataName::RESERVE, new_reserve);
	model_data = data;
	if (old_enabled != new_enabled)
	{
		apply_enabled(new_enabled);
	}
	if (old_reserve != new_reserve)
	{
		bool enabled = false;
		model_data.get(ModelData::DataName::ENABLE, enabled);
		if (enabled)
		{
			SteerGear_SetPosition(new_reserve ? 4 : 2);
		}
	}
}

void SteeringGear::apply_enabled(bool enabled)
{
	SteerGear_SetPosition(enabled ? 2 : 0);
}
