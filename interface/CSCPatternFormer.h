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
        CSCPatternFormer(){min_valid_el_ = 0;};
        ~CSCPatternFormer(){};
        CSCPatternCollection formPatterns(const std::vector<Hit>& vhit, const DetectorSegmentationBase& segmentation);
        void setMinValidElements(int mve) {min_valid_el_ = mve;}
    private:
        int min_valid_el_;

};

#endif