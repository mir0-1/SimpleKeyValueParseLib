#pragma once
#include <string>

class ValueWrapper
{
	private:
		bool nullReference;
		std::string value;

	public:
		const std::string& getAsString() const;
		int getAsInt() const;
		bool getAsBool() const;
		bool isNull() const;
		bool isInt() const;

		ValueWrapper(const std::string& value);
		ValueWrapper();
};
