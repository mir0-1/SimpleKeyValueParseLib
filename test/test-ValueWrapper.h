#include "../src/main/ValueWrapper.h"
#include "../../SimpleTestingLibrary/assert.h"
#include "test-configuration.h"

void test_ValueWrapper_validInt()
{
	ValueWrapper test("123");

	assertTrue(!test.isNull(), exitOnFail, "Testing ValueWrapper not null (int)", testLogger);
	assertTrue(test.isInt(), exitOnFail, "Testing ValueWrapper is int", testLogger);
	assertTrue(test.getAsInt() == 123, exitOnFail, "Testing ValueWrapper string-to-int conversion", testLogger);
}

void test_ValueWrapper_invalidInt()
{
	ValueWrapper test("1a23");

	assertTrue(!test.isNull(), exitOnFail, "Testing ValueWrapper not null (invalid int)", testLogger);
	assertTrue(!test.isInt(), exitOnFail, "Testing ValueWrapper is not int (invalid int)", testLogger);
}

void test_ValueWrapper_validBool()
{
	ValueWrapper test("1");

	assertTrue(!test.isNull(), exitOnFail, "Testing ValueWrapper not null (bool)", testLogger);
	assertTrue(test.getAsBool() == true ,exitOnFail, "Testing ValueWrapper string-to-bool conversion", testLogger);
}

void test_ValueWrapper_invalidBool()
{
	ValueWrapper test("true");

	assertTrue(!test.isNull(), exitOnFail, "Testing ValueWrapper not null (invalid bool)", testLogger);
	assertTrue(test.getAsBool() == false ,exitOnFail, "Testing ValueWrapper string-to-bool conversion (invalid bool)", testLogger);
}
