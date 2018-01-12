#include "ThetaPhiSegmentation.h"

PatternElement<> ThetaPhiSegmentation::getPatternElement (const Hit& hit) const
{
    if (coords_ == kEMTF)
        return getPE_EMTFCoords(hit);
    else if (coords_ == kAnglesDeg)
        return getPE_AngleDegCoords(hit);
    else
        throw std::logic_error("Invalid coordinate initialization"); // FIXME: move to a more meaningful exceptio
}


PatternElement<> ThetaPhiSegmentation::getPE_EMTFCoords (const Hit& hit) const
{
    if (hit.type == (int) Subsystem::kCSC)
        return PatternElement<> (
                bins_CSC_theta .at(hit.station-1).findBin(hit.emtf_theta),
                bins_CSC_phi   .at(hit.station-1).findBin(hit.emtf_phi)
            );
    return invalid_pattern_element_;
}

PatternElement<> ThetaPhiSegmentation::getPE_AngleDegCoords (const Hit& hit) const
{
    // sim_theta and sim_phi are expressed n degrees
    if (hit.type == (int) Subsystem::kCSC)
        return PatternElement<> (
                bins_CSC_theta .at(hit.station-1).findBin(hit.sim_theta),
                bins_CSC_phi   .at(hit.station-1).findBin(hit.sim_phi)
            );
    return invalid_pattern_element_;
}