//
// Copyright (c) 2013-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BEAST_STRING_HPP
#define BEAST_STRING_HPP

#include <boost/spirit/home/support/char_encoding/ascii.hpp>
#include <boost/utility/string_ref.hpp>

namespace beast {

/// The type of string view used by the library
using string_view = boost::string_ref;

/// The type of basic string view used by the library
template<class CharT, class Traits>
using basic_string_view =
    boost::basic_string_ref<CharT, Traits>;

namespace detail {

template<class = void>
bool
iequals(
    beast::string_view const& lhs,
    beast::string_view const& rhs)
{
    auto n = lhs.size();
    if(rhs.size() != n)
        return false;
    auto p1 = lhs.data();
    auto p2 = rhs.data();
    using namespace boost::spirit::char_encoding;
    while(n--)
        if(ascii::tolower(*p1) != ascii::tolower(*p2))
            return false;
    return true;
}

} // detail

/** Returns `true` if two strings are equal, using a case-insensitive comparison.

    The case-comparison operation is defined only for low-ASCII characters.

    @param lhs The string on the left side of the equality

    @param rhs The string on the right side of the equality
*/
inline
bool
iequals(
    beast::string_view const& lhs,
    beast::string_view const& rhs)
{
    return detail::iequals(lhs, rhs);
}

/** A strictly less predicate for strings, using a case-insensitive comparison.

    The case-comparison operation is defined only for low-ASCII characters.
*/
struct iless
{
    bool
    operator()(
        beast::string_view const& lhs,
        beast::string_view const& rhs) const
    {
        using std::begin;
        using std::end;
        using namespace boost::spirit::char_encoding;
        return std::lexicographical_compare(
            begin(lhs), end(lhs), begin(rhs), end(rhs),
            [](char lhs, char rhs)
            {
                return ascii::tolower(lhs) < ascii::tolower(rhs);
            }
        );
    }
};

/** A predicate for string equality, using a case-insensitive comparison.

    The case-comparison operation is defined only for low-ASCII characters.
*/
struct iequal
{
    bool
    operator()(
        beast::string_view const& lhs,
        beast::string_view const& rhs) const
    {
        return iequals(lhs, rhs);
    }
};

} // beast

#endif