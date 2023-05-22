#pragma once
#include "CommonIterableMap.h"

class CommonMutableMap : public CommonIterableMap
{
	private:
		std::unordered_map<std::string, ValueWrapper> map;
		std::unordered_map<std::string, ValueWrapper>::const_iterator it;

	public:
		virtual const ValueWrapper& getValue(const std::string& key) const;
		virtual void setValue(const std::string& key, const ValueWrapper& value);
		virtual char* parseKeyValuePairs(char* src, char separator, char terminator);

		virtual bool hasKey(const std::string& key) const override;
		std::pair<std::string, ValueWrapper> getNextPairFromIterator() override;
		virtual void resetIterator() override;
		virtual bool isIteratorReset() const override;
		virtual bool isIteratorAtEnd() const override;

		CommonMutableMap();
};
