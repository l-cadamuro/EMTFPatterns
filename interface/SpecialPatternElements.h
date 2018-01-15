#ifndef SPECIALPATTERNELEMENTS_H
#define SPECIALPATTERNELEMENTS_H

/*
** class  : SpecialPatternElements
** author : L. Cadamuro (UF)
** date   : 12/01/2018
** brief  : Some pattern codes with a special meaning to the pattern formers
**        : note: they should all be negative!
*/

#include "Pattern.h"

namespace SpecialPatternElements
{
    static const PatternElement<> missing_element_ (-999, -999);  // when there is no hit in that specific spot
    static const PatternElement<> invalid_element_ (-888, -888);  // when the hit is outside the range defined in the segmentation

    static bool isValidPatternElement (const PatternElement<> pe){
        return (pe.first >= 0 && pe.second >= 0);
    }
}

#endif
