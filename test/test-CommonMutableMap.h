#include "../src/template/CommonMutableMap.h"
#include "../../SimpleTestingLibrary/assert.h"
#include "test-configuration.h"

struct TestStruct
{
	int data;
	std::string sth;
};

typedef CommonMutableMap<int, TestStruct> MapUnderTest;

void test_CommonMutableMap_checkPresence()
{
	MapUnderTest map;
	TestStruct myStruct;

	myStruct.data = 23;
	myStruct.sth = "hello";

	map.setValue(1337, myStruct);

	assertTrue(map.hasKey(1337), exitOnFail, "Testing if map has int key", testLogger);

	const TestStruct& value = map.getValue(1337);
	const TestStruct& valueAgain = map.getValue(1337);

	assertTrue(&value != &myStruct, exitOnFail, "Testing if structs have different addresses", testLogger);
	assertTrue(&value == &valueAgain, exitOnFail, "Testing if getting the same value twice does not have unique address", testLogger);

	assertTrue(value.data == 23, exitOnFail, "Testing if struct field data is copied correctly", testLogger);
	assertTrue(value.sth == "hello", exitOnFail, "Testing if struct field sth is copied correctly", testLogger);
}

void test_CommonMutableMap_checkOverride_sameStruct()
{
	MapUnderTest map;
	TestStruct myStruct;

	myStruct.data = 23;
	myStruct.sth = "hello";

	map.setValue(1337, myStruct);

	myStruct.data = 32;
	myStruct.sth = "goodbye";

	map.setValue(1337, myStruct);

	assertTrue(map.hasKey(1337), exitOnFail, "Testing if map has int key (override, same struct)", testLogger);

	const TestStruct& value = map.getValue(1337);
	const TestStruct& valueAgain = map.getValue(1337);

	assertTrue(&value != &myStruct, exitOnFail, "Testing if structs have different addresses (override, same struct)", testLogger);
	assertTrue(&value == &valueAgain, exitOnFail, "Testing if getting the same value twice does not have unique address (override, same struct)", testLogger);

	assertTrue(value.data == 32, exitOnFail, "Testing if struct field data is copied correctly (override, same struct)", testLogger);
	assertTrue(value.sth == "goodbye", exitOnFail, "Testing if struct field sth is copied correctly (override, same struct)", testLogger);
}

void test_CommonMutableMap_checkOverride_differentStruct()
{
	MapUnderTest map;
	TestStruct myStruct;

	myStruct.data = 23;
	myStruct.sth = "hello";

	map.setValue(1337, myStruct);

	TestStruct differentStruct;
	differentStruct.data = 32;
	differentStruct.sth = "goodbye";

	map.setValue(1337, differentStruct);

	assertTrue(map.hasKey(1337), exitOnFail, "Testing if map has int key (override, diff struct)", testLogger);

	const TestStruct& value = map.getValue(1337);

	assertTrue(value.data == 32, exitOnFail, "Testing if struct field data is copied correctly (override, diff struct)", testLogger);
	assertTrue(value.sth == "goodbye", exitOnFail, "Testing if struct field sth is copied correctly (override, diff struct)", testLogger);
}

void test_CommonMutableMap_checkRemoval()
{
	MapUnderTest map;
	TestStruct myStruct;

	myStruct.data = 23;
	myStruct.sth = "hello";

	map.setValue(512, myStruct);
	map.removeKey(512);

	assertTrue(!map.hasKey(512), exitOnFail, "Testing if key-value pair was removed", testLogger);
}
