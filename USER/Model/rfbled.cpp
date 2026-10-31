#include "rfbled.h"

bool Rfbled::init()
{
	return false;
}

void Rfbled::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IOutputModel*>(this), mode);
}


void Rfbled::set_model_data(const ModelData& data)
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

void Rfbled::apply_enabled(bool enabled)
{
}
