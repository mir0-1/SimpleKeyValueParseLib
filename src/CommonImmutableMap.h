#pragma once
#include "CommonMutableMap.h"

class CommonImmutableMap : public CommonIterableMap
{
	private:
		CommonMutableMap& map;

	public:
		const ValueWrapper& getValue(const std::string& key) const;

		virtual bool hasKey(const std::string& key) const override;
		virtual std::pair<std::string, ValueWrapper> getNextPairFromIterator() override;
		virtual void resetIterator() override;
		virtual bool isIteratorReset() const override;
		virtual bool isIteratorAtEnd() const override;

		CommonImmutableMap(CommonMutableMap& map);
};
