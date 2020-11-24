#include <gtest/gtest.h>
#include "../twoHashTable.h"

TEST(TwoHashTable, readFile) {
	std::string filepath(__FILE__);
	filepath = filepath.substr(0, filepath.find_last_of('/'));
	chdir(filepath.c_str());
	TwoHashTable result("../grocery_upc_database.csv", 10000);
	EXPECT_EQ(result.entries().size(), 110433);
}

TEST(TwoHashTable, parse) {
	struct Test {
		std::string text;
		bool expectThrow;
		TwoHashTable expected;
	};

	std::vector<Test> tests {
		{
			"",
			false,
			TwoHashTable(),
		},
		{
			"a",
			true,
			TwoHashTable(),
		},
		{
			"0,",
			false,
			TwoHashTable({{0, ""}}),
		},
		{
			"0,a",
			false,
			TwoHashTable({{0, "a"}}),
		},
		{
			"0,aaa",
				false,
				TwoHashTable({{0, "aaa"}}),
		},
		{
			"0,aaa\n1,aaa\n",
			false,
			TwoHashTable({{0, "aaa"}, {1, "aaa"}}),
		},
		{
			"035200264013,Riceland American Jazmine Rice\n"
			"011111065925,Caress Velvet Bliss Ultra Silkening Beauty Bar - 6 Ct\n",
			false,
			TwoHashTable({
				{35200264013, "Riceland American Jazmine Rice"},
				{11111065925, "Caress Velvet Bliss Ultra Silkening Beauty Bar - 6 Ct"},
			}),
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		std::stringstream ss(tests[i].text);
		if (tests[i].expectThrow) {
			EXPECT_THROW(TwoHashTable::parse(ss, 2), std::runtime_error) << i;
		} else {
			EXPECT_EQ(TwoHashTable::parse(ss, 2), tests[i].expected) << i;
		}
	}

	std::stringstream ss("0,");
	EXPECT_THROW(TwoHashTable::parse(ss, 0), std::runtime_error);
}

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
		{
			TwoHashTable({{0, "aaa"}}, 1),
			{0, "aaa"},
			TwoHashTable({{0, "aaa"}, {0, "aaa"}}),
		},
		{
			TwoHashTable({}, 2),
			{0, "aaa"},
			TwoHashTable({{0, "aaa"}}),
		},
		{
			TwoHashTable({{0, "aaa"}}, 2),
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

TEST(TwoHashTable, search) {
	struct Test {
		TwoHashTable table;
		UPCEntry item;
		Position expected;
	};

	std::vector<Test> tests {
		{
			TwoHashTable({}),
			{0, ""},
			Position::notFound(),
		},
		{
			TwoHashTable({}),
			{0, "aaa"},
			Position::notFound(),
		},
		{
			TwoHashTable({{0, "aaa"}}),
			{0, "aaa"},
			{0, 0},
		},
		{
			TwoHashTable({{1, "aaa"}}, 2),
			{1, "aaa"},
			{1, 0},
		},
		{
			TwoHashTable({{0, "aaa"}, {1, "aaa"}}, 1),
			{1, "aaa"},
			{0, 1},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		EXPECT_EQ(tests[i].table.search(tests[i].item), tests[i].expected) << i;
	}
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
			{0, ""},
			10,
			{{0, 0}},
		},
		{
			{0, "a"},
			10,
			{{0, 7}},
		},
		{
			{0, "aa"},
			10,
			{{0, 6}},
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

TEST(TwoHashTable, getStddev) {
	struct Test {
		TwoHashTable table;
		double expected;
	};

	std::vector<Test> tests {
		{
			TwoHashTable({{0, "aaa"}}, 1),
			0,
		},
		{
			TwoHashTable({{0, "aaa"}, {1, "aaa"}}, 1),
			0,
		},
		{
			TwoHashTable({
				{0, "aaa"},
				{1, "aaa"},
				{2, "aaa"},
			}, 2),
			0.5,
		},
		{
			TwoHashTable({
				{0, "aaa"},
				{0, "aaa"},
				{1, "aaa"},
			}, 3),
			0.81649658092772603,
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		EXPECT_EQ(tests[i].table.getStdDev(), tests[i].expected) << i;
	}

	EXPECT_TRUE(std::isnan(TwoHashTable().getStdDev()));
}