#ifndef ETAPHISEGMENTATION_H
#define ETAPHISEGMENTATION_H

#include "DetectorSegmentationBase.h"
#include "Boundaries.h"
#include "Subsystem.h"

class ThetaPhiSegmentation : public DetectorSegmentationBase
{
    public:
        enum Station{
            kS1 = 0,
            kS2 = 1,
            kS3 = 2,
            kS4 = 3
        }; // because stations will start at pos 0 of an array

        enum CoordsType{
            kEMTF      = 0,
            kAnglesDeg = 1
        };

        ThetaPhiSegmentation(){coords_ = kEMTF;}
        ~ThetaPhiSegmentation(){};

        PatternElement<> getPatternElement (const Hit& hit) const;

        void setUseEMTFCoords()     {coords_ = kEMTF;}
        void setUseAngleDegCoords() {coords_ = kAnglesDeg;}

        // ---------------------

        // leave public, so that the user can set them directly

        std::array<Boundaries<float>, 4> bins_CSC_theta;
        std::array<Boundaries<float>, 4> bins_CSC_phi;

    private:
        CoordsType coords_;
        PatternElement<> getPE_EMTFCoords     (const Hit& hit) const;
        PatternElement<> getPE_AngleDegCoords (const Hit& hit) const;

};

#endif