#pragma once

/*********************************************************************/
//
//			Copyright 2022 Max J. Martin
//
//			This file is part of APM.
// 
//			APM is free software : you can redistribute it
//			and /or modify it under the terms of the GNU General
//			Public License as published by the Free Software
//			Foundation, either version 3 of the License, or
//			(at your option) any later version.
//			
//			APM is distributed in the hope that it will be
//			useful, but WITHOUT ANY WARRANTY; without even the
//			implied warranty of MERCHANTABILITY or FITNESS FOR
//			A PARTICULAR PURPOSE.See the GNU General Public
//			
//			You should have received a copy of the GNU General
//			Public License along with APM.If not, see
//			< https://www.gnu.org/licenses/>.
//			
/*********************************************************************/

#if __cplusplus >= 202002L
#include <format>
#endif
#include <iosfwd>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <string_view>
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <vector>

#ifdef _MSC_VER
#include "Windows.h"
#endif

/*  Place holder for porting over to another operating system.
#ifdef _MSC_VER

#else

#endif

*/

namespace Olly {

    /********************************************************************************************/
    //
    //                             Fundamental Type Declarations
    //
    //          The declarations below should be used throughout the entire project.
    //
    /********************************************************************************************/

    typedef     std::string          Text;
    typedef     std::stringstream    Text_Stream;
    typedef     std::vector<Text>    Text_Tokens;

    static const double NOT_A_NUMBER = std::numeric_limits<double>::quiet_NaN();

    static const std::hash<Text> DEFAULT_HASH_FUNCTION;

    template<typename S, typename T>
    class is_streamable
    {
        template<typename SS, typename TT>
        static auto test(int)
            -> decltype(std::declval<SS&>() << std::declval<TT>(), std::true_type());

        template<typename, typename>
        static auto test(...) -> std::false_type;

    public:
        static const bool value = decltype(test<S, T>(0))::value;
    };
}