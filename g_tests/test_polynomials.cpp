#include "../tables/polynomials.h"
#include "gtest/gtest.h"
#include "gtest/gtest_prod.h"

TEST(polynomials, delete_spaces_) {
	c_monomial a("5 x^2* y ^3*z^ 4*x^2 + 2x^1 *y^2* z^4");
	ASSERT_NO_THROW(a.delete_spaces());
}

TEST(polynomials, check_correctness) {
	c_monomial a("5 x^2* y ^3*z^ 4*x^2 + 2x^1 *y^2* z^4");
	ASSERT_NO_THROW(a.check_correctness());
}

TEST(polynomials, check_empty) {
	c_monomial a("5 x^2* y ^3*z^ 4*x^2 + 2x^1 *y^2* z^4");
	EXPECT_EQ(a.is_empty(), 0);
}

TEST(polynomials, check_empty_failed) {
	c_monomial a("");
	EXPECT_EQ(a.is_empty(), 1);
}

TEST(polynomials, check_monom_factor) {
	c_polynomial a("7x^4*y^3*z^4");
	EXPECT_EQ(a.get_monomial_factor(), "434");
}

TEST(polynomials, check_monom_coefficient) {
	c_polynomial a("7x^4*y^3*2z^4");
	EXPECT_EQ(a.get_monomial_coefficient(), 14);
}

TEST(polynomials, check_polynomials_is_equual) {
	c_polynomial a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	c_polynomial b("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	EXPECT_EQ(a == b, true);
}

TEST(polynomials, check_multiply_by_constant) {
	c_polynomial a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	c_polynomial res("4.00x^1*y^2*z^4+10.00x^4*y^3*z^4");
	EXPECT_EQ(true, a * 2 == res);
}

TEST(polynomials, check_multiply_by_negative_constant) {
	c_polynomial a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	c_polynomial res("-10.00x^1*y^2*z^4+-25.00x^4*y^3*z^4");
	EXPECT_EQ(a * -5 == res, true);
}

TEST(polynomials, check_multiply_by_zero) {
	c_polynomial a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	c_polynomial res("0");
	EXPECT_EQ(a * 0 == res, true);
}

TEST(polynomials, check_sum) {
	c_polynomial a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	c_polynomial b("7x^4*y^3*z^4 + 15x^1*y^2*z^4");
	c_polynomial res("17.00x^1*y^2*z^4+12.00x^4*y^3*z^4");
	EXPECT_EQ(a + b == res, true);
}

TEST(polynomials, check_difference_of_equal_polynomials) {
	c_polynomial a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	c_polynomial b("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	c_polynomial res("0");
	EXPECT_EQ(a - b == res, true);
}

TEST(polynomials, check_difference_of_notequal_polynomials) {
	c_polynomial a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	c_polynomial b("7x^4*y^3*z^4 + 15x^1*y^2*z^4");
	c_polynomial res("-13.00x^1*y^2*z^4+-2.00x^4*y^3*z^4");
	EXPECT_EQ(a - b == res, true);
}

TEST(polynomials, check_multiply_of_two_polynomials) {
	c_polynomial a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	c_polynomial b("7x^4*y^3*z^4 + 15x^1*y^2*z^4");
	c_polynomial res("30.00x^2*y^4*z^8+89.00x^5*y^5*z^8+35.00x^8*y^6*z^8");
	EXPECT_EQ(a * b == res, true);
}

TEST(polynomials, pause) {
	system("pause");
}