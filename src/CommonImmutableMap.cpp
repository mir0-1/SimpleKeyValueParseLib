#include "CommonImmutableMap.h"

bool CommonImmutableMap::hasKey(const std::string& key) const
{
	return map.hasKey(key);
}

const ValueWrapper& CommonImmutableMap::getValue(const std::string& key) const
{
	return map.getValue(key);
}

std::pair<std::string, ValueWrapper> CommonImmutableMap::getNextPairFromIterator()
{
	return map.getNextPairFromIterator();
}

void CommonImmutableMap::resetIterator()
{
	return map.resetIterator();
}

bool CommonImmutableMap::isIteratorAtEnd() const
{
	return map.isIteratorAtEnd();
}

bool CommonImmutableMap::isIteratorReset() const
{
	return map.isIteratorReset();
}

CommonImmutableMap::CommonImmutableMap(CommonMutableMap& map)
	:	map(map)
{
}
