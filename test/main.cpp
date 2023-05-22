#include "test-CommonMutableMap.h"

int main()
{
	std::cout << "[--------------------TESTING CommonMutableMap now--------------------]" << std::endl;
	test_CommonMutableMap_insertKeyValuePairs();
	test_CommonMutableMap_iterateKeyValuePairs();
	test_CommonMutableMap_iterateEmpty();
	test_CommonMutableMap_parse_simpleQueryLikeParams();
	test_CommonMutableMap_parse_simpleQueryMidTerminated();
	test_CommonMutableMap_parse_queryMidTerminated_multipleSeparators();
	test_CommonMutableMap_parse_configFile_multipleSeparators();
	test_CommonMutableMap_parse_configFile_multipleSeparatorsCRLF();
	test_CommonMutableMap_parse_configFile_multipleSeparatorsCRLF_extraCR();
	test_CommonMutableMap_parse_configFile_multipleSeparatorsCRLF_multipleEquals();
	test_CommonMutableMap_parse_simpleQuery_spaceChaos();
	test_CommonMutableMap_parse_simpleQuery_emptyValue();
	test_CommonMutableMap_parse_simpleQuery_noValue();
	test_CommonMutableMap_parse_simpleQuery_noValue_multipleKeyValueSeparators();
	test_CommonMutableMap_parse_simpleQuery_noKey();
	test_CommonMutableMap_parse_justEquals();
}
