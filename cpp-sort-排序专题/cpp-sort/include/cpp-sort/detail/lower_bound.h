/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Morwenn
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef CPPSORT_DETAIL_LOWER_BOUND_H_
#define CPPSORT_DETAIL_LOWER_BOUND_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <functional>
#include <iterator>
#include <cpp-sort/utility/as_function.h>
#include <cpp-sort/utility/functional.h>

namespace cppsort
{
namespace detail
{
    template<
        typename ForwardIterator,
        typename T,
        typename Compare = std::less<>,
        typename Projection = utility::identity
    >
    auto lower_bound(ForwardIterator first, ForwardIterator last,
                     const T& value,
                     Compare compare={}, Projection projection={})
        -> ForwardIterator
    {
        auto&& proj = utility::as_function(projection);

        auto size = std::distance(first, last);
        while (size > 0)
        {
            ForwardIterator it = first;
            std::advance(it, size / 2);
            if (compare(proj(*it), value))
            {
                first = ++it;
                size -= size / 2 + 1;
            }
            else
            {
                size /= 2;
            }
        }
        return first;
    }
}}

#endif // CPPSORT_DETAIL_LOWER_BOUND_H_
