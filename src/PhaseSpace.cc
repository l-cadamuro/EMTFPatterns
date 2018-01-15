#include "PhaseSpace.h"

PhaseSpaceElement PhaseSpace::getPhaseSpaceElement(float pt, float eta, float phi)
{
    float pt_value = pt;
    if (use_one_over_pt_)
        pt_value = (pt_value > 0 ? 1./pt_value : 0);

    int ptbin  = ptBins().findBin( pt_value );
    int etabin = ptBins().findBin( eta );
    int phibin = ptBins().findBin( phi );

    PhaseSpaceElement pse;
    pse.at(Coords::pt)  = ptbin;
    pse.at(Coords::eta) = etabin;
    pse.at(Coords::phi) = phibin;

    return pse;
}