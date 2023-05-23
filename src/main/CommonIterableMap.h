#pragma once
#include <string>
#include <unordered_map>

template <class K, class V>
class CommonIterableMap
{
	public:
		virtual bool hasKey(const K& key) const = 0;
		virtual std::pair<K, V> getNextPairFromIterator() = 0;
		virtual void resetIterator() = 0;
		virtual bool isIteratorReset() const = 0;
		virtual bool isIteratorAtEnd() const = 0;
};
