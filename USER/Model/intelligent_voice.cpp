#include "intelligent_voice.h"

bool IntelligentVoice::init()
{
	return true;
}

void IntelligentVoice::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IFunctionalModel*>(this), mode);
}

void IntelligentVoice::update()
{
	model_data.set(ModelData::DataName::READY, false);
}
