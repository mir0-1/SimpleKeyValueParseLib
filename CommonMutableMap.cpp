#include "CommonMutableMap.h"

const ValueWrapper& CommonMutableMap::getValue(const std::string& key) const
{
	static ValueWrapper nullKey;

	auto iter = map.find(key);
	if (iter != map.end())
		return iter->second;
	return nullKey;
}

void CommonMutableMap::setValue(const std::string& key, const ValueWrapper& value)
{
	map[key] = value;
}

char* CommonMutableMap::parseKeyValuePairs(char* src, char separator, char terminator)
{
	int keyStartIndex = -1;
	int valueStartIndex = -1;
	bool isLast = false;
	bool isTerminatorSpace = false;
	bool isTerminatorNewline = false;
	bool isSeparatorNewline = false;

	int i;
	for (i = 0; ; i++)
	{
		isSeparatorNewline = (separator == '\n');
		isTerminatorNewline = (terminator == '\n');
		isTerminatorSpace = (!isTerminatorNewline && isspace(terminator));
		isLast = (src[i] == terminator);

		if (!isTerminatorSpace && valueStartIndex == -1 && !isLast && isspace(src[i]))
			continue;
		
		if (keyStartIndex == -1)
			keyStartIndex = i;

		if (terminator != '\0' && src[i] == '\0')
			return nullptr;

		if (src[i] == '=')
		{
			valueStartIndex = i + 1;
			continue;
		}

		if (src[i] == separator || isLast)
		{
			if (valueStartIndex != -1)
			{
				int keyEndIndex = valueStartIndex - 1;
				int valueEndIndex = i;

				char tempKeyChar = src[keyEndIndex];
				char tempValueChar = src[valueEndIndex];

				src[keyEndIndex] = '\0';
				src[valueEndIndex] = '\0';

				bool hasCRbeforeNewline = ((isTerminatorNewline && isLast) || isSeparatorNewline) && valueEndIndex >= 1 && src[valueEndIndex - 1] == '\r';
				if (hasCRbeforeNewline)
					src[valueEndIndex - 1] = '\0';

				setValue(src + keyStartIndex, ValueWrapper(src + valueStartIndex));

				if (hasCRbeforeNewline)
					src[valueEndIndex - 1] = '\r';

				src[keyEndIndex] = tempKeyChar;
				src[valueEndIndex] = tempValueChar;
			}

			keyStartIndex = -1;
			valueStartIndex = -1;
		}

		if (isLast)
			break;
	}

	return src + i + 1;
}

bool CommonMutableMap::hasKey(const std::string& key) const
{
	return map.find(key) != map.end();
}

std::pair<std::string, ValueWrapper> CommonMutableMap::getNextPairFromIterator()
{
	it++;

	if (isIteratorAtEnd())
		resetIterator();

	return std::make_pair(it->first, it->second);
}

bool CommonMutableMap::isIteratorAtEnd() const
{
	return it == map.cend();
}

void CommonMutableMap::resetIterator()
{
	it = map.cbegin();
}

bool CommonMutableMap::isIteratorReset() const
{
	return it == map.cbegin();
}

CommonMutableMap::CommonMutableMap()
{
	resetIterator();
}
