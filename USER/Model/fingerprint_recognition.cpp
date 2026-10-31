#include "fingerprint_recognition.h"

bool FingerprintRecognition::init()
{
	return true;
}

void FingerprintRecognition::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IFunctionalModel*>(this), mode);
}

void FingerprintRecognition::update()
{
	model_data.set(ModelData::DataName::READY, false);
}
