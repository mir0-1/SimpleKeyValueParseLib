#include "ValueWrapper.h"

std::string ValueWrapper::getAsString() const
{
	return value;
}

int ValueWrapper::getAsInt() const
{
	return atoi(value.c_str());
}

bool ValueWrapper::getAsBool() const
{
	return (bool)getAsInt();
}

bool ValueWrapper::isNull() const
{
	return nullReference;
}

ValueWrapper::ValueWrapper(const std::string& value)
{
	this->value = value;
	nullReference = false;
}

ValueWrapper::ValueWrapper()
{
	nullReference = true;
}
