/****************************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <map>

// class map

// size_type max_size() const;

#include <cassert>
#include "libcxx_tc_common.h"
#include <limits>
#include <map>
#include <type_traits>

#include "test_allocator.h"
#include "test_macros.h"

int tc_libcxx_containers_map_access_max_size(void)
{
  typedef std::pair<const int, int> KV;
  {
    typedef limited_allocator<KV, 10> A;
    typedef std::map<int, int, std::less<int>, A> C;
    C c;
    TC_ASSERT_EXPR(c.max_size() <= 10);
    LIBCPP_ASSERT(c.max_size() == 10);
  }
  {
    typedef limited_allocator<KV, (size_t)-1> A;
    typedef std::map<int, int, std::less<int>, A> C;
    C c;
    TC_ASSERT_EXPR(c.max_size() <= (size_t)-1);
    LIBCPP_ASSERT(c.max_size() == (size_t)-1);
    }
    {
      typedef std::map<char, int> C;
      const C::difference_type max_dist =
          std::numeric_limits<C::difference_type>::max();
      C c;
      TC_ASSERT_EXPR(c.max_size() <= max_dist);
      TC_ASSERT_EXPR(c.max_size() <= alloc_max_size(c.get_allocator()));
    }
    TC_SUCCESS_RESULT();
    return 0;
}
