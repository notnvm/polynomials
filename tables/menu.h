#pragma once

#include <stdlib.h>

#include "polynomials.h"

namespace other {
	class c_menu {
	public:
		c_menu() {};
		~c_menu() {};
	public:
		void init();
		void rules();
		void get_polynomials();
		void sum();
		void difference();
		void multiply_by_const();
		void multiply();

	};
}