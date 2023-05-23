#include "test-CommonParsableMap.h"
#include "test-CommonMutableMap.h"
#include "../src/template/CommonImmutableMap.h"

int main()
{
	CommonParsableMap dummy0;
	CommonMutableMap<int, int> dummy1;
	CommonImmutableMap<int, int> dummy2(dummy1);

	std::cout << "[--------------------TESTING CommonMutableMap now--------------------]" << std::endl;
	test_CommonMutableMap_checkPresence();
	test_CommonMutableMap_checkOverride_sameStruct();
	test_CommonMutableMap_checkOverride_differentStruct();
	test_CommonMutableMap_checkRemoval();

	std::cout << "[--------------------TESTING CommonParsableMap now--------------------]" << std::endl;
	test_CommonParsableMap_insertKeyValuePairs();
	test_CommonParsableMap_iterateKeyValuePairs();
	test_CommonParsableMap_iterateEmpty();
	test_CommonParsableMap_parse_simpleQueryLikeParams();
	test_CommonParsableMap_parse_simpleQueryMidTerminated();
	test_CommonParsableMap_parse_queryMidTerminated_multipleSeparators();
	test_CommonParsableMap_parse_configFile_multipleSeparators();
	test_CommonParsableMap_parse_configFile_multipleSeparatorsCRLF();
	test_CommonParsableMap_parse_configFile_multipleSeparatorsCRLF_extraCR();
	test_CommonParsableMap_parse_configFile_multipleSeparatorsCRLF_multipleEquals();
	test_CommonParsableMap_parse_simpleQuery_spaceChaos();
	test_CommonParsableMap_parse_simpleQuery_emptyValue();
	test_CommonParsableMap_parse_simpleQuery_noValue();
	test_CommonParsableMap_parse_simpleQuery_noValue_multipleKeyValueSeparators();
	test_CommonParsableMap_parse_simpleQuery_noKey();
	test_CommonParsableMap_parse_justEquals();
	test_CommonParsableMap_toString();
}
