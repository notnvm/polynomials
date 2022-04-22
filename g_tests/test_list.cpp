#include "../tables/list.h"

#include "gtest/gtest.h"

TEST(list, can_create_list) {
	ASSERT_NO_THROW(list<double> l);
}

TEST(list, check_copy_constructor_list) {
	list<double> l_1;
	l_1.push_front(1);
	l_1.push_front(2);
	ASSERT_NO_THROW(list<double> l_2(l_1));
}

TEST(list, check_size_list) {
	list<double> l_1;
	l_1.push_front(1);
	l_1.push_front(2);
	EXPECT_EQ(l_1.size(), 2);
}

TEST(list, can_create_iterator_for_dummyhead_list) {
	list<double> l_1;
	l_1.push_front(1);
	ASSERT_NO_THROW(auto it = l_1.dummy_head());
}

TEST(list, can_create_const_iterator_for_dummyhead_list) {
	list<double> l_1;
	l_1.push_front(1);
	ASSERT_NO_THROW(auto it = l_1.cdummy_head());
}

TEST(list, can_create_iterator_list) {
	list<double> l_1;
	l_1.push_front(1);
	ASSERT_NO_THROW(auto it = l_1.begin());
}

TEST(list, can_create_const_iterator_list) {
	list<double> l_1;
	l_1.push_front(1);
	ASSERT_NO_THROW(auto it = l_1.cbegin());
}

TEST(list, check_iterator_list) {
	list<double> l_1;
	l_1.push_front(1);
	auto it = l_1.begin();
	EXPECT_EQ(*it, 1);
}

TEST(list, can_create_end_iterator_list) {
	list<double> l_1;
	l_1.push_front(1);
	ASSERT_NO_THROW(auto it = l_1.end());
}

TEST(list, can_create_const_end_iterator_list) {
	list<double> l_1;
	l_1.push_front(1);
	ASSERT_NO_THROW(auto it = l_1.cend());
}

TEST(list, check_postfix_iterator_list) {
	list<double> l_1;
	l_1.push_front(3);
	l_1.push_front(2);
	l_1.push_front(1);
	auto it = l_1.begin();
	EXPECT_EQ(*(it++), 1);
}

TEST(list, check_prefix_iterator_list) {
	list<double> l_1;
	l_1.push_front(3);
	l_1.push_front(2);
	l_1.push_front(1);
	auto it = l_1.begin();
	++it;
	EXPECT_EQ(*it, 2);
}

TEST(list, check_push_front) {
	list<double> l_1;
	l_1.push_front(1);
	l_1.push_front(2);
	l_1.push_front(3);
	l_1.push_front(4);
	EXPECT_EQ(l_1.size(), 4);
}

TEST(list, check_pop_front) {
	list<double> l_1;
	l_1.push_front(1);
	l_1.push_front(2);
	l_1.push_front(3);
	l_1.push_front(4);
	l_1.pop_front();
	l_1.pop_front();
	EXPECT_EQ(l_1.size(), 2);
}

TEST(list, check_front) {
	list<double> l_1;
	l_1.push_front(1);
	l_1.push_front(2);
	l_1.push_front(3);
	l_1.push_front(4);
	l_1.pop_front();
	EXPECT_EQ(l_1.front(), 3);
}

TEST(list, check_front_2) {
	list<double> l_1;
	l_1.push_front(1);
	l_1.push_front(2);
	l_1.push_front(3);
	l_1.push_front(4);
	l_1.pop_front();
	l_1.pop_front();
	EXPECT_EQ(l_1.front(), 2);
}

TEST(list, check_is_empty) {
	list<double> l_1;
	l_1.push_front(3);
	EXPECT_EQ(l_1.empty(), 0);
}

TEST(list, check_is_empty_2) {
	list<double> l_1;
	EXPECT_EQ(l_1.empty(), 1);
}

TEST(list, check_merge) {
	list<double> l_1, l_2;
	l_1.push_front(2);
	l_1.push_front(1);
	l_2.push_front(4);
	l_2.push_front(3);
	l_1.merge(l_2);
	EXPECT_EQ(l_1.size(), 4);
}

TEST(list, check_sort) {
	list<double> l_1;
	l_1.push_front(22);
	l_1.push_front(3);
	l_1.push_front(13);
	l_1.push_front(41);
	l_1.sort();
	l_1.pop_front();
	l_1.pop_front();
	EXPECT_EQ(l_1.front(), 22);
}