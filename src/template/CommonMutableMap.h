#pragma once
#include "../main/CommonIterableMap.h"

template <class K, class V>
class CommonMutableMap : public CommonIterableMap<K, V>
{
	protected:
		typename std::unordered_map<K, V> map;
		typename std::unordered_map<K, V>::const_iterator it;

	public:
		virtual const V& getValue(const K& key) const;
		virtual void setValue(const K& key, const V& value);
		virtual void removeKey(const K& key);

		virtual bool hasKey(const K& key) const override;
		virtual std::pair<K, V> getNextPairFromIterator() override;
		virtual void resetIterator() override;
		virtual bool isIteratorReset() const override;
		virtual bool isIteratorAtEnd() const override;

		CommonMutableMap();
};

#include "CommonMutableMap.cpp"
