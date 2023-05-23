#include "CommonParsableMap.h"

char* CommonParsableMap::parseKeyValuePairs(char* src, char separator, char terminator)
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

std::string CommonParsableMap::toString()
{
	std::string result;

	resetIterator();

	while (!isIteratorAtEnd())
	{
		std::pair<std::string, ValueWrapper> pair = getNextPairFromIterator();

		result.append(pair.first);
		result.append("=");
		result.append(pair.second.getAsString());
		result.append("\r\n");

		if (isIteratorReset())
			break;
	}

	return result;
}
