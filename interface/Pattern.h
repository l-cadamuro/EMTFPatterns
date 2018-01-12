#ifndef PATTERN_H
#define PATTERN_H

/*
** class  : Pattern
** author : L. Cadamuro (UF)
** brief  : class representing in an abstract way an EMTF pattern
** notes  : - a "PatternElement" is a combination of two values (first = theta and second = phi)
**          - a "Pattern" is a collection of an arbitrary (but fixed) number of "PatternElement"
*/

#include <utility>
#include <array>

template <typename T1 = int, typename T2 = int>           using PatternElement = std::pair<T1, T2> ;
template <size_t S, typename T1 = int, typename T2 = int> using Pattern        = std::array<PatternElement<T1,T2>, S> ;

#endif