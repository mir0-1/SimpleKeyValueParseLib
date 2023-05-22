#pragma once
#include "CommonMutableMap.h"
#include "../SimpleTestingLibrary/assert.h"
#include "test-configuration.h"

void printParseInput(char* parseInput)
{
	if (testLogger != nullptr)
	{
		(*testLogger) << "-------------------------------" << std::endl;
		(*testLogger) << "Parsing the following" << std::endl << parseInput << std::endl;
	}
}

void test_CommonMutableMap_insertKeyValuePairs()
{
	CommonMutableMap map;

	map.setValue("test", ValueWrapper("1234"));
	map.setValue("alpha", ValueWrapper("more"));
	map.setValue("rabbit", ValueWrapper("1"));

	assertTrue(map.hasKey("test"), exitOnFail, "Testing if test is present in map", testLogger);
	assertTrue(map.hasKey("alpha"), exitOnFail, "Testing if alpha is present in map", testLogger);
	assertTrue(map.hasKey("rabbit"), exitOnFail, "Testing if rabbit is present in map", testLogger);

	assertTrue(map.getValue("test").getAsInt() == 1234, exitOnFail, "Testing test value correctness", testLogger);
	assertTrue(map.getValue("alpha").getAsString() == "more", exitOnFail, "Testing alpha value correctness", testLogger);
	assertTrue(map.getValue("rabbit").getAsBool() == true, exitOnFail, "Testing rabbit value correctness", testLogger);
}

void test_CommonMutableMap_iterateKeyValuePairs()
{
	CommonMutableMap map;

	const char* expectedKeysForIteration[] = {"test", "alpha", "rabbit"};
	const char* expectedValuesForIteration[] = {"1234", "more", "1"};
	int index;

	map.setValue("test", ValueWrapper("1234"));
	map.setValue("alpha", ValueWrapper("more"));
	map.setValue("rabbit", ValueWrapper("1"));

	const int expectedIterationCount = 3;
	int actualIterationCount = 0;
	std::cout << "Starting iteration now..." << std::endl;
	map.resetIterator();
	while (!map.isIteratorAtEnd())
	{
		std::cout << "At iteration " << actualIterationCount << std::endl;
		std::pair<std::string, ValueWrapper> pair = map.getNextPairFromIterator();

		for(index = 0; pair.first != expectedKeysForIteration[index] && index < 3; index++);

		assertTrue(pair.first == expectedKeysForIteration[index], exitOnFail, "Testing iteration key", testLogger);
		assertTrue(pair.second.getAsString() == expectedValuesForIteration[index], exitOnFail, "Testing iteration value", testLogger);
		actualIterationCount++;

		if (map.isIteratorReset())
			break;

	}

	assertTrue(actualIterationCount == expectedIterationCount, exitOnFail, "Testing overall iteration count", testLogger);
}

void test_CommonMutableMap_iterateEmpty()
{
	CommonMutableMap map;

	const int expectedIterationCount = 0;
	int actualIterationCount = 0;
	map.resetIterator();
	while (!map.isIteratorAtEnd())
	{
		actualIterationCount++;

		std::pair<std::string, ValueWrapper> pair = map.getNextPairFromIterator();

		if (map.isIteratorReset())
			break;
	}

	assertTrue(expectedIterationCount == actualIterationCount, exitOnFail, "Testing overall iteration count (should not iterate)", testLogger);
}

void test_CommonMutableMap_parse_simpleQueryLikeParams()
{
	CommonMutableMap map;
	char src[] = "myvalue=1&anotherV=test";

	printParseInput(src);

	map.parseKeyValuePairs(src, '&', '\0');

	assertTrue(map.hasKey("myvalue"), exitOnFail, "Testing presence of key called myvalue", testLogger);
	assertTrue(map.hasKey("anotherV"), exitOnFail, "Testing presence of key called anotherV", testLogger);
	assertTrue(map.getValue("myvalue").getAsInt() == 1, exitOnFail, "Testing value of key called anotherV", testLogger);
	assertTrue(map.getValue("anotherV").getAsString() == "test", exitOnFail, "Testing value of key called anotherV", testLogger);
}

void test_CommonMutableMap_parse_simpleQueryMidTerminated()
{
	CommonMutableMap map;
	char src[] = "myvalue=1&+anotherV=test";

	printParseInput(src);

	map.parseKeyValuePairs(src, '&', '+');

	assertTrue(map.hasKey("myvalue"), exitOnFail, "Testing presence of key called myvalue (mid terminator \'+\')'", testLogger);
	assertTrue(!map.hasKey("anotherV"), exitOnFail, "Testing absence of key called anotherV (mid terminator \'+\')", testLogger);
	assertTrue(map.getValue("myvalue").getAsInt() == 1, exitOnFail, "Testing value of key called anotherV (mid terminator \'+\')", testLogger);
}

void test_CommonMutableMap_parse_queryMidTerminated_multipleSeparators()
{
	CommonMutableMap map;
	char src[] = "&&myvalue=1&&somethingElse=yes&&&&&+anotherV=test&&&";

	printParseInput(src);

	map.parseKeyValuePairs(src, '&', '+');

	assertTrue(map.hasKey("myvalue"), exitOnFail, "Testing presence of key called myvalue (mid terminator \'+\', multiple &)'", testLogger);
	assertTrue(!map.hasKey("anotherV"), exitOnFail, "Testing absence of key called anotherV (mid terminator \'+\', multiple &)", testLogger);
	assertTrue(map.getValue("myvalue").getAsInt() == 1, exitOnFail, "Testing value of key called myvalue (mid terminator \'+\', multiple &)", testLogger);
	assertTrue(map.hasKey("somethingElse"), exitOnFail, "Testing presence of key called somethingElse (mid terminator \'+\', multiple &)'", testLogger);
	assertTrue(map.getValue("somethingElse").getAsString() == "yes", exitOnFail, "Testing value of key called somethingElse (mid terminator \'+\', multiple &)'", testLogger);
}

void test_CommonMutableMap_parse_configFile_multipleSeparators()
{
	CommonMutableMap map;
	char src[] = "\n\nmyvalue=1\n\nsomethingElse=yes\n\n\nanotherV=test\n\n\n";

	printParseInput(src);

	map.parseKeyValuePairs(src, '\n', '\0');

	assertTrue(map.hasKey("myvalue"), exitOnFail, "Testing presence of key called myvalue (config-like, \\n multiple separator)'", testLogger);
	assertTrue(map.hasKey("anotherV"), exitOnFail, "Testing prsence of key called anotherV ((config-like, \\n multiple separator)", testLogger);
	assertTrue(map.getValue("myvalue").getAsInt() == 1, exitOnFail, "Testing value of key called myvalue (config-like, \\n multiple separator)", testLogger);
	assertTrue(map.getValue("anotherV").getAsString() == "test", exitOnFail, "Testing value of key called anotherV (config-like, \\n multiple separator)", testLogger);
	assertTrue(map.hasKey("somethingElse"), exitOnFail, "Testing presence of key called somethingElse (config-like, \\n multiple separator)", testLogger);
	assertTrue(map.getValue("somethingElse").getAsString() == "yes", exitOnFail, "Testing value of key called somethingElse (config-like, \\n multiple separator)", testLogger);
}

void test_CommonMutableMap_parse_configFile_multipleSeparatorsCRLF()
{
	CommonMutableMap map;
	char src[] = "\r\n\r\nmyvalue=1\r\n\r\nsomethingElse=yes\r\n\r\nanotherV=test\r\n";

	printParseInput(src);

	map.parseKeyValuePairs(src, '\n', '\0');

	assertTrue(map.hasKey("myvalue"), exitOnFail, "Testing presence of key called myvalue (config-like, \\r\\n multiple separator)", testLogger);
	assertTrue(map.hasKey("anotherV"), exitOnFail, "Testing presence of key called anotherV (config-like, \\r\\n multiple separator)", testLogger);
	assertTrue(map.getValue("myvalue").getAsString() == "1", exitOnFail, "Testing value of key called myvalue (config-like, \\r\\n multiple separator)", testLogger);
	assertTrue(map.getValue("anotherV").getAsString() == "test", exitOnFail, "Testing value of key called anotherV (config-like, \\r\\n multiple separator)", testLogger);
	assertTrue(map.hasKey("somethingElse"), exitOnFail, "Testing presence of key called somethingElse (config-like, \\r\\n multiple separator)", testLogger);
	assertTrue(map.getValue("somethingElse").getAsString() == "yes", exitOnFail, "Testing value of key called somethingElse (config-like, \\r\\n multiple separator)", testLogger);
}

void test_CommonMutableMap_parse_configFile_multipleSeparatorsCRLF_extraCR()
{
	CommonMutableMap map;
	char src[] = "\r\n\r\nmyvalue=1\r\n\r\nsomethingElse=yes\r\r\n\r\nanotherV=test\r\n";

	printParseInput(src);

	map.parseKeyValuePairs(src, '\n', '\0');

	assertTrue(map.hasKey("myvalue"), exitOnFail, "Testing presence of key called myvalue (config-like, \\r\\n multiple separator, extra \\r)", testLogger);
	assertTrue(map.hasKey("anotherV"), exitOnFail, "Testing presence of key called anotherV (config-like, \\r\\n multiple separator, extra \\r)", testLogger);
	assertTrue(map.getValue("myvalue").getAsString() == "1", exitOnFail, "Testing value of key called myvalue (config-like, \\r\\n multiple separator, extra \\r)", testLogger);
	assertTrue(map.getValue("anotherV").getAsString() == "test", exitOnFail, "Testing value of key called anotherV (config-like, \\r\\n multiple separator, extra \\r)", testLogger);
	assertTrue(map.hasKey("somethingElse"), exitOnFail, "Testing presence of key called somethingElse (config-like, \\r\\n multiple separator, extra \\r)", testLogger);
	assertTrue(map.getValue("somethingElse").getAsString() == "yes\r", exitOnFail, "Testing value of key called somethingElse (config-like, \\r\\n multiple separator, extra \\r)", testLogger);
}

void test_CommonMutableMap_parse_configFile_multipleSeparatorsCRLF_multipleEquals()
{
	CommonMutableMap map;
	char src[] = "\r\n\r\nmyvalue==p==1\r\n\r\nsomethingElse===yes\r\n\r\nanotherV===test\r\n";

	printParseInput(src);

	map.parseKeyValuePairs(src, '\n', '\0');

	assertTrue(map.hasKey("myvalue==p="), exitOnFail, "Testing presence of key called myvalue==p= (config-like, \\r\\n multiple separator, multiple =)", testLogger);
	assertTrue(map.hasKey("anotherV=="), exitOnFail, "Testing presence of key called anotherV== (config-like, \\r\\n multiple separator, multiple =)", testLogger);
	assertTrue(map.getValue("myvalue==p=").getAsString() == "1", exitOnFail, "Testing value of key called myvalue==p= (config-like, \\r\\n multiple separator, multiple =)", testLogger);
	assertTrue(map.getValue("anotherV==").getAsString() == "test", exitOnFail, "Testing value of key called anotherV== (config-like, \\r\\n multiple separator, multiple =)", testLogger);
	assertTrue(map.hasKey("somethingElse=="), exitOnFail, "Testing presence of key called somethingElse== (config-like, \\r\\n multiple separator, multiple =)", testLogger);
	assertTrue(map.getValue("somethingElse==").getAsString() == "yes", exitOnFail, "Testing value of key called somethingElse== (config-like, \\r\\n multiple separator, multiple =)", testLogger);
}

void test_CommonMutableMap_parse_simpleQuery_spaceChaos()
{
	CommonMutableMap map;
	char src[] = "myv  alu  e=1  &ano  ther V=te st  ";
 
	printParseInput(src);

	map.parseKeyValuePairs(src, '&', '\0');

	assertTrue(map.hasKey("myv  alu  e"), exitOnFail, "Testing presence of key called \'myv  alu  e\' (space chaos)", testLogger);
	assertTrue(map.hasKey("ano  ther V"), exitOnFail, "Testing presence of key called \'ano  ther V\' (space chaos)", testLogger);
	assertTrue(map.getValue("myv  alu  e").getAsString() == "1  ", exitOnFail, "Testing value of key called \'myv  alu  e\' (space chaos)", testLogger);
	assertTrue(map.getValue("ano  ther V").getAsString() == "te st  ", exitOnFail, "Testing value of key called \'ano  ther V\' (space chaos)", testLogger);
}

void test_CommonMutableMap_parse_simpleQuery_emptyValue()
{
	CommonMutableMap map;
	char src[] = "myvalue=&anotherV=test";
 
	printParseInput(src);

	map.parseKeyValuePairs(src, '&', '\0');

	assertTrue(map.hasKey("myvalue"), exitOnFail, "Testing presence of key called myvalue (empty value)", testLogger);
	assertTrue(map.hasKey("anotherV"), exitOnFail, "Testing presence of key called anotherV (empty value)", testLogger);
	assertTrue(map.getValue("myvalue").getAsString() == "", exitOnFail, "Testing value of key called myvalue (empty value)", testLogger);
	assertTrue(map.getValue("anotherV").getAsString() == "test", exitOnFail, "Testing value of key called anotherV (empty value)", testLogger);
}

void test_CommonMutableMap_parse_simpleQuery_noValue()
{
	CommonMutableMap map;
	char src[] = "myvalue&anotherV=test";
 
	printParseInput(src);

	map.parseKeyValuePairs(src, '&', '\0');

	assertTrue(!map.hasKey("myvalue"), exitOnFail, "Testing absence of key called myvalue (no value)", testLogger);
	assertTrue(map.hasKey("anotherV"), exitOnFail, "Testing presence of key called anotherV (no value)", testLogger);
	assertTrue(map.getValue("anotherV").getAsString() == "test", exitOnFail, "Testing value of key called anotherV (no value)", testLogger);
}

void test_CommonMutableMap_parse_simpleQuery_noValue_multipleKeyValueSeparators()
{
	CommonMutableMap map;
	char src[] = "myvalue&&&anotherV=test&&";
 
	printParseInput(src);

	map.parseKeyValuePairs(src, '&', '\0');

	assertTrue(!map.hasKey("myvalue"), exitOnFail, "Testing absence of key called myvalue (no value, multiple &)", testLogger);
	assertTrue(map.hasKey("anotherV"), exitOnFail, "Testing presence of key called anotherV (no value, multiple &)", testLogger);
	assertTrue(map.getValue("anotherV").getAsString() == "test", exitOnFail, "Testing value of key called anotherV (no value, multiple &)", testLogger);
}

void test_CommonMutableMap_parse_simpleQuery_noKey()
{
	CommonMutableMap map;
	char src[] = "=myvalue&anotherV=test";
 
	printParseInput(src);

	map.parseKeyValuePairs(src, '&', '\0');

	assertTrue(map.hasKey(""), exitOnFail, "Testing presence of key \"\" (intentional empty string) (no key)", testLogger);
	assertTrue(!map.hasKey("="), exitOnFail, "Testing absence of key \"=\" (no key)", testLogger);
	assertTrue(!map.hasKey("myvalue"), exitOnFail, "Testing absence of key called myvalue (no key)", testLogger);
	assertTrue(map.hasKey("anotherV"), exitOnFail, "Testing presence of key called anotherV (no key)", testLogger);
	assertTrue(map.getValue("anotherV").getAsString() == "test", exitOnFail, "Testing value of key called anotherV (no key)", testLogger);
}

void test_CommonMutableMap_parse_justEquals()
{
	CommonMutableMap map;
	char src[] = "=";
 
	printParseInput(src);

	map.parseKeyValuePairs(src, '&', '\0');

	assertTrue(map.hasKey(""), exitOnFail, "Testing presence of key \"\" (intentional empty string) (just equals sign)", testLogger);
	assertTrue(map.getValue("").getAsString() == "", exitOnFail, "Testing value of key \"\" (intentional empty string) (just equals sign)", testLogger);
}
