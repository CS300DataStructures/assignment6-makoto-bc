#include "../UPCEntry.h"
#include <gtest/gtest.h>

TEST(UPCEntry, readStringConstructor) {
	UPCEntry e("753950001954,Doctor's Best Best Curcumin C3 Complex 1000mg Tablets - 120 Ct");
	EXPECT_EQ(e.upc, 753950001954);
	EXPECT_EQ(e.name, "Doctor's Best Best Curcumin C3 Complex 1000mg Tablets - 120 Ct");
}

TEST(UPCEntry, parse) {
	struct Test {
		std::string text;
		bool expectThrow;
		UPCEntry expected;
	};

	std::vector<Test> tests {
		{ // 0
			"",
			true,
			{},
		},
		{ // 1
			",",
			true,
			{},
		},
		{ // 2
			",a",
			true,
			{},
		},
		{ // 3
			"0",
			true,
			{},
		},
		{ // 4
			"0,",
			false,
			{0, ""},
		},
		{ // 5
			"0,a",
			false,
			{0, "a"},
		},
		{ // 6
			"0 a",
			true,
			{},
		},
		{ // 7
			"0,a\nb",
			false,
			{0, "a"},
		},
		{ // 8
			"035200264013,Riceland American Jazmine Rice\n",
			false,
			{35200264013, "Riceland American Jazmine Rice"},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		std::stringstream ss(tests[i].text);
		if (tests[i].expectThrow) {
			EXPECT_THROW(UPCEntry::parse(ss), std::runtime_error) << i;
		} else {
			UPCEntry result;
			EXPECT_NO_THROW(result = UPCEntry::parse(ss)) << i;
			EXPECT_EQ(result, tests[i].expected) << i;
		}
	}
}