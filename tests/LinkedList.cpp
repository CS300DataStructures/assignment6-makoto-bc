#include <gtest/gtest.h>
#include "../LinkedList.h"

TEST(List, initializerListConstructor) {
	{
		List<int> expected;
		EXPECT_EQ(List<int>({}), expected);
	}
	{
		List<int> expected;
		expected.insert(0, 0);
		EXPECT_EQ(List<int>({0}), expected);
	}
	{
		List<int> expected;
		expected.insert(0, 0);
		expected.insert(1, 1);
		expected.insert(2, 2);
		EXPECT_EQ(List<int>({0, 1, 2}), expected);
	}
}

TEST(List, copyConstructor) {
	{
		List<int> list0;
		List<int> list1 = list0; // NOLINT(performance-unnecessary-copy-initialization)
		EXPECT_EQ(list1, List<int>());
	}
	{
		List<int> list0({0});
		List<int> list1 = list0; // NOLINT(performance-unnecessary-copy-initialization)
		EXPECT_EQ(list1, list0);
	}
	{
		List<int> list0({0, 1});
		List<int> list1 = list0; // NOLINT(performance-unnecessary-copy-initialization)
		EXPECT_EQ(list1, list0);
	}
}

TEST(List, insert) {
	{
		List<int> list;
		EXPECT_EQ(list, List<int>());
		EXPECT_THROW(list.insert(1, 0), std::out_of_range);
		list.insert(0, 0);
		EXPECT_EQ(list, List<int>({0}));
		list.insert(1, 1);
		EXPECT_EQ(list, List<int>({0, 1}));
		list.insert(2, 2);
		EXPECT_EQ(list, List<int>({0, 1, 2}));
	}
	{
		List<int> list;
		list.insert(0, 0);
		EXPECT_EQ(list, List<int>({0}));
		list.insert(0, 1);
		EXPECT_EQ(list, List<int>({1, 0}));
		list.insert(0, 2);
		EXPECT_EQ(list, List<int>({2, 1, 0}));
	}
	{
		List<int> list({0, 1});
		list.insert(1, 2);
		EXPECT_EQ(list, List<int>({0, 2, 1}));
	}
}

TEST(List, remove) {
	struct Test {
		List<int> list;
		size_t index;
		List<int> expected;
	};

	std::vector<Test> tests {
		{
			{0},
			0,
			{},
		},
		{
			{0, 1},
			0,
			{1},
		},
		{
			{0, 1},
			1,
			{0},
		},
		{
			{0, 1, 2},
			0,
			{1, 2},
		},
		{
			{0, 1, 2},
			1,
			{0, 2},
		},
		{
			{0, 1, 2},
			2,
			{0, 1},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		tests[i].list.remove(tests[i].index);
		EXPECT_EQ(tests[i].list, tests[i].expected) << i;
	}

	EXPECT_THROW(List<int>().remove(0), std::out_of_range);
	EXPECT_THROW(List<int>({0}).remove(1), std::out_of_range);
}

TEST(List, nodeAt) {
	{
		List<int> list;
		EXPECT_THROW(list.nodeAt(0), std::out_of_range);
	}
	{
		List<int> list({0, 1, 2});
		EXPECT_EQ(list.nodeAt(0).value, 0);
		EXPECT_EQ(list.nodeAt(1).value, 1);
		EXPECT_EQ(list.nodeAt(2).value, 2);
		EXPECT_THROW(list.nodeAt(3), std::out_of_range);
	}
}