#include "ValueWrapper.h"

const std::string& ValueWrapper::getAsString() const
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

bool ValueWrapper::isInt() const
{
	if (value.empty())
		return false;

    std::string::const_iterator it = value.begin();
    while (it != value.end() && std::isdigit(*it)) ++it;
    return !value.empty() && it == value.end();
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
