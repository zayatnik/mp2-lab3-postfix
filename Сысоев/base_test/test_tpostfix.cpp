#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>
#include <string>

TEST(TPostfix, can_create_postfix) {
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TStack, can_create_copied_postfix) {
	TPostfix p;
	ASSERT_NO_THROW(TPostfix p1(p));
}

TEST(TPostfix, can_get_infix) {
	TPostfix p("1+2");
	EXPECT_EQ("1+2", p.GetInfix());
}


TEST(TPostfix, can_create_postfix_from_infix) {
	TPostfix p("1+(2-3)*4-5+6");
	p.ToPostfix();
	EXPECT_EQ("1;2;3;-;4;*;+;5;-;6;+;", p.GetPostfix());
}

TEST(TPostfix, can_create_object_with_correct_infix) {
	ASSERT_NO_THROW(TPostfix p("1+2"));
}

TEST(TPostfix, CheckInfix_return_false_when_infix_is_invalid) {
	ASSERT_ANY_THROW(TPostfix p("(1+-2"););
}

TEST(TStack, throw_when_division_by_zero) {
	TPostfix p("2+2/0");
	ASSERT_ANY_THROW(p.Calculate());
}


TEST(TPostfix, can_calculate_expression) {
	TPostfix p("(1+2)-3/6*2");
	p.ToPostfix();
	EXPECT_EQ(2, p.Calculate());
}