#include "../polinoms/gtest/gtest.h"

#include "../polinoms/polinom.h"

TEST(polynomials, delete_spaces) {
	polinoms a("5 x^2* y ^3*z^ 4*x^2 + 2x^1 *y^2* z^4");
	ASSERT_NO_THROW(a.delete_spaces());
}

TEST(polynomials, check_correctness) {
	polinoms a("5 x^2* y ^3*z^ 4*x^2 + 2x^1 *y^2* z^4");
	ASSERT_NO_THROW(a.check_correctness());
}

TEST(polynomials, check_empty) {
	polinoms a("5 x^2* y ^3*z^ 4*x^2 + 2x^1 *y^2* z^4");
	EXPECT_EQ(a.is_empty(), 0);
}

TEST(polynomials, check_empty_failed) {
	polinoms a;
	EXPECT_EQ(a.is_empty(), 1);
}

TEST(polynomials, check_symbols) {
	polinoms a("5 x^2* y ^3*z^ 4*x^2 + 2x^1 *y^2* z^4");
	ASSERT_NO_THROW(a.check_symbols());
}

TEST(polynomials, check_monom_factor) {
	monoms a("7x^4*y^3*z^4");
	EXPECT_EQ(a.getMonomFactor(), "434");
}

TEST(polynomials, check_monom_coefficient) {
	monoms a("7x^4*y^3*2z^4");
	EXPECT_EQ(a.getMonomCoefficient(), 14);
}

TEST(polynomials, check_polynomials_is_equual) {
	polinoms a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	polinoms b("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	EXPECT_EQ(a == b, true);
}

TEST(polynomials, check_multiply_by_constant) {
	polinoms a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	polinoms res("4.00x^1*y^2*z^4+10.00x^4*y^3*z^4");
	EXPECT_EQ(a*2 == res, true);
}

TEST(polynomials, check_multiply_by_negative_constant) {
	polinoms a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	polinoms res("-10.00x^1*y^2*z^4+-25.00x^4*y^3*z^4");
	EXPECT_EQ(a * -5 == res, true);
}

TEST(polynomials, check_multiply_by_zero) {
	polinoms a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	polinoms res("0");
	EXPECT_EQ(a * 0 == res, true);
}

TEST(polynomials, check_sum) {
	polinoms a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	polinoms b("7x^4*y^3*z^4 + 15x^1*y^2*z^4");
	polinoms res("17.00x^1*y^2*z^4+12.00x^4*y^3*z^4");
	EXPECT_EQ(a + b == res, true);
}

TEST(polynomials, check_difference_of_equal_polynomials) {
	polinoms a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	polinoms b("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	polinoms res("0");
	EXPECT_EQ(a - b == res, true);
}

TEST(polynomials, check_difference_of_notequal_polynomials) {
	polinoms a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	polinoms b("7x^4*y^3*z^4 + 15x^1*y^2*z^4");
	polinoms res("-13.00x^1*y^2*z^4+-2.00x^4*y^3*z^4");
	EXPECT_EQ(a - b == res, true);
}

TEST(polynomials, check_multiply_of_two_polynomials) {
	polinoms a("5x^2*y^3*z^4*x^2 + 2x^1*y^2*z^4");
	polinoms b("7x^4*y^3*z^4 + 15x^1*y^2*z^4");
	polinoms res("30.00x^2*y^4*z^8+89.00x^5*y^5*z^8+35.00x^8*y^6*z^8");
	EXPECT_EQ(a * b == res, true);
}

TEST(polynomials, pause) {
	system("pause");
}