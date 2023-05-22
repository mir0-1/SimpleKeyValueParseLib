#pragma once
#include <string>
#include <unordered_map>
#include "ValueWrapper.h"

class CommonIterableMap
{
	public:
		virtual bool hasKey(const std::string& key) const = 0;
		virtual std::pair<std::string, ValueWrapper> getNextPairFromIterator() = 0;
		virtual void resetIterator() = 0;
		virtual bool isIteratorReset() const = 0;
		virtual bool isIteratorAtEnd() const = 0;
};
