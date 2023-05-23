#pragma once
#include "CommonMutableMap.h"

template <class K, class V>
class CommonImmutableMap : public CommonIterableMap<K, V>
{
	private:
		CommonMutableMap& map;

	public:
		const ValueWrapper& getValue(const K& key) const;

		virtual bool hasKey(const K& key) const override;
		virtual std::pair<K, V> getNextPairFromIterator() override;
		virtual void resetIterator() override;
		virtual bool isIteratorReset() const override;
		virtual bool isIteratorAtEnd() const override;

		CommonImmutableMap<K, V>(CommonMutableMap& map);
};

#include "CommonImmutableMap.cpp"
