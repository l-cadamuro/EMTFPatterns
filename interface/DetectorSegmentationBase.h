#ifndef DETECTORSEGMENTATIONBASE_H
#define DETECTORSEGMENTATIONBASE_H

/*
** class  : DetectorSegmentation
** author : L. Cadamuro (UF)
** brief  : abstract representation of the segmentation of a detector portion in two dimensions (x/y, theta/phi, etc)
**        : it is the general interface with the pattern formers
*/

#include "Pattern.h"
#include "Hit.h"

class DetectorSegmentationBase{
    public:
        DetectorSegmentationBase(){}
        ~DetectorSegmentationBase(){}
        virtual PatternElement<> getPatternElement (const Hit& hit) const = 0; // abstract interface for any "geometry" os superstrips / superhits / etc...
        const static PatternElement<> invalid_pattern_element_; // whatever is invalid for the detector segmentation
};

#endif