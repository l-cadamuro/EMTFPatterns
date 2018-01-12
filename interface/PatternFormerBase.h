#ifndef PATTERNFORMERBASE_H
#define PATTERNFORMERBASE_H

/*
** class  : PatternFormer
** author : L. Cadamuro (UF)
** brief  : utilities for building and booking EMTF patterns
** notes  : - a "PatternElement" is a combination of two values (first = theta and second = phi)
**          - a "Pattern" is a collection of an arbitrary (but fixed) number of "PatternElement"
*/

#include <iostream>
#include <utility>
#include <array>
#include <vector>
#include <string>
#include "Pattern.h"
#include "Hit.h"
#include "Subsystem.h"
#include "DetectorSegmentationBase.h"

// ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - 

template<size_t S>
using PatternCollection = std::vector<Pattern<S>>;

// general base class, templated on the number of hits forming a pattern
template <size_t S>
class PatternFormerBase {
    public:

        // static const PatternElement<> missing_element_;

        PatternFormerBase(){};
        ~PatternFormerBase(){};
        // virtual std::vector<Pattern<S>> formPatterns(const std::vector<Hit>& vhit, const DetectorSegmentationBase& segmentation) = 0;
        virtual PatternCollection<S> formPatterns(const std::vector<Hit>& vhit, const DetectorSegmentationBase& segmentation) = 0;
        static std::string patternElement_toString(PatternElement<> pe);
        static std::string pattern_toString(Pattern<S> p);

        // bool operator == (const PatternFormerBase<S>& rhs) const;
        // Pattern<S> getPattern() const {return pattern_;}
    // protected:
    //     Pattern<S> pattern_;
};

// template <size_t S>
// const PatternElement<> PatternFormerBase<S>::missing_element_  = {-999, -999}; // code used for a missing pattern element

template <size_t S>
std::string PatternFormerBase<S>::patternElement_toString(PatternElement<> pe)
{
    std::string s;
    s += "(" ;
    s += std::to_string(pe.first) ;
    s += ", " ;
    s += std::to_string(pe.second) ;
    s += ")";
    return s;
}

template <size_t S>
std::string PatternFormerBase<S>::pattern_toString(Pattern<S> p)
{
    std::string s;
    for (auto& pe : p)
    {
        s += patternElement_toString(pe) + " ";
    }
    return s;
}

// template <size_t S>
// bool PatternFormerBase<S>::operator == (const PatternFormerBase<S>& rhs) const
// {
//     return (this -> pattern_ == rhs.pattern_);
// }


#endif