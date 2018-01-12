#ifndef CSCPATTERNFORMER_H
#define CSCPATTERNFORMER_H

/*
** class  : CSCPatternFormer
** author : L. Cadamuro (UF)
** brief  : specialization of the PatternFormerBase to build a pattern only with the CSC information
*/

#include "PatternFormerBase.h"

using CSCPattern           = Pattern<4>;
using CSCPatternCollection = PatternCollection<4>;

// a pattern made only of CSCs hits
class CSCPatternFormer : public PatternFormerBase<4> {
    public:
        CSCPatternFormer(){};
        ~CSCPatternFormer(){};
        CSCPatternCollection formPatterns(const std::vector<Hit>& vhit, const DetectorSegmentationBase& segmentation);
};

#endif