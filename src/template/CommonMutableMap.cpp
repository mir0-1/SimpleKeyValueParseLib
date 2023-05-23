template <class K, class V>
const V& CommonMutableMap<K, V>::getValue(const K& key) const
{
	static V nullKey;

	auto iter = map.find(key);
	if (iter != map.end())
		return iter->second;
	return nullKey;
}

template <class K, class V>
void CommonMutableMap<K, V>::setValue(const K& key, const V& value)
{
	map[key] = value;
}

template <class K, class V>
void CommonMutableMap<K, V>::removeKey(const K& key)
{
	map.erase(key);
}

template <class K, class V>
bool CommonMutableMap<K, V>::hasKey(const K& key) const
{
	return map.find(key) != map.end();
}

template <class K, class V>
std::pair<K, V> CommonMutableMap<K, V>::getNextPairFromIterator()
{
	it++;

	if (isIteratorAtEnd())
		resetIterator();

	return std::make_pair(it->first, it->second);
}

template <class K, class V>
bool CommonMutableMap<K, V>::isIteratorAtEnd() const
{
	return it == map.cend();
}

template <class K, class V>
void CommonMutableMap<K, V>::resetIterator()
{
	it = map.cbegin();
}

template <class K, class V>
bool CommonMutableMap<K, V>::isIteratorReset() const
{
	return it == map.cbegin();
}

template <class K, class V>
CommonMutableMap<K, V>::CommonMutableMap()
{
	resetIterator();
}
