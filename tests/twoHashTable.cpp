#include <gtest/gtest.h>
#include "../twoHashTable.h"

TEST(TwoHashTable, insert) {
	struct Test {
		TwoHashTable table;
		UPCEntry entry;
		TwoHashTable expected;
	};

	std::vector<Test> tests {
		{
			TwoHashTable({}, 1),
			{0, "aaa"},
			TwoHashTable({{0, "aaa"}}),
		},
		{
			TwoHashTable({{0, "aaa"}}, 1),
			{1, "aaa"},
			TwoHashTable({{0, "aaa"}, {1, "aaa"}}),
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		EXPECT_TRUE(tests[i].table.insert(tests[i].entry));
		EXPECT_EQ(tests[i].table, tests[i].expected) << i;
	}

	EXPECT_EQ(TwoHashTable().insert({0, ""}), false);
}

TEST(TwoHashTable, getHash) {
	struct Test {
		UPCEntry entry;
		size_t tableSize;
		Option<Hash> expected;
	};

	std::vector<Test> tests {
		{
			{0, ""},
			0,
			{},
		},
		{
			{0, "aaa"},
			0,
			{},
		},
		{
			{1, "aaa"},
			10,
			{{1, 9}},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		EXPECT_EQ(getHash(tests[i].entry, tests[i].tableSize), tests[i].expected) << i;
	}
}