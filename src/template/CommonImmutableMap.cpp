template <class K, class V>
bool CommonImmutableMap<K, V>::hasKey(const K& key) const
{
	return map.hasKey(key);
}

template <class K, class V>
const ValueWrapper& CommonImmutableMap<K, V>::getValue(const K& key) const
{
	return map.getValue(key);
}

template <class K, class V>
std::pair<K, V> CommonImmutableMap<K, V>::getNextPairFromIterator()
{
	return map.getNextPairFromIterator();
}

template <class K, class V>
void CommonImmutableMap<K, V>::resetIterator()
{
	return map.resetIterator();
}

template <class K, class V>
bool CommonImmutableMap<K, V>::isIteratorAtEnd() const
{
	return map.isIteratorAtEnd();
}

template <class K, class V>
bool CommonImmutableMap<K, V>::isIteratorReset() const
{
	return map.isIteratorReset();
}

template <class K, class V>
CommonImmutableMap<K, V>::CommonImmutableMap(CommonMutableMap<K, V>& map)
	:	map(map)
{
}
