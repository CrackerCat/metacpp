/*
 * Meta C++ Tool and Library
 * Copyright (C) 2022  Keith Hammond
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string_view>
#include <tuple>

#include "metacpp/meta.hpp"

#include "../../test.hpp"

class [[my::attrib(1, "2", 3.0)]] example{
	public:
		void method1(std::string_view s) const noexcept;
		void method1(const std::string &str) noexcept;

		std::tuple<int, float, char> method2();
};

class example_test_derived: public TestTemplateClass<std::string_view>{

};

namespace ex{
	namespace detail{
		template<typename Ts>
		class helper;

		template<typename ... Ts>
		class helper<meta::types<Ts...>>: public TestTemplateClass<Ts>...{};

		template<typename Ts>
		class helper_helper: public ex::detail::helper<Ts>{
			template<typename ... Us>
			ex::detail::helper<meta::types<Us...>> rebind(){
				return {};
			}

			ex::detail::helper<Ts> &self(){ return *this; }
		};
	}

	template<typename ... Ts>
	class example_test_helped: public ex::detail::helper_helper<meta::types<Ts...>>{

	};
}

enum class example_enum{
	case_0 = 69,
	case_1 = 420,
	case_2 = 1337
};

inline example_enum example_fn(){
	return example_enum::case_0;
}
