#pragma once
#include <string>

class ValueWrapper
{
	private:
		bool nullReference;
		std::string value;

	public:
		std::string getAsString() const;
		int getAsInt() const;
		bool getAsBool() const;
		bool isNull() const;

		ValueWrapper(const std::string& value);
		ValueWrapper();
};
