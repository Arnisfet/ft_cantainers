//
// Created by arnisfet on 10.05.2022.
//

#ifndef FT_CANTAINERS_FT_TYPE_TRAITS_H
#define FT_CANTAINERS_FT_TYPE_TRAITS_H

#include <type_traits>
#include <iostream>

namespace ft {

	template <bool B, class T = void>
	struct enable_if;

	template <class T>
	struct enable_if <true, T> {
		typedef T type;
};
}

#endif //FT_CANTAINERS_FT_TYPE_TRAITS_H
