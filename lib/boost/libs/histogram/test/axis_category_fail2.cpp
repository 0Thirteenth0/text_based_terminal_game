// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/histogram/axis/category.hpp>

using namespace boost::histogram;

int main() {
  // growing category axis cannot have entries in overflow bin
  (void)axis::category<int, boost::use_default,
                       decltype(axis::option::growth | axis::option::overflow)>({1, 2});
}