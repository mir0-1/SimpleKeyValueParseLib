#include "../template/CommonMutableMap.h"
#include "ValueWrapper.h"

class CommonParsableMap : public CommonMutableMap<std::string, ValueWrapper>
{
	public:
		char* parseKeyValuePairs(char* src, char separator, char terminator);
		std::string toString();
};
