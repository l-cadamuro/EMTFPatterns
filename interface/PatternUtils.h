#ifndef PATTERNUTILS_H
#define PATTERNUTILS_H

#include "Pattern.h"
#include "Hit.h"
#include <vector>
#include <iostream>

namespace PatternUtils
{

    template <size_t S>
    unsigned int nValidHits(Pattern<S> p)
    {
        unsigned int nhits = 0;
        for (auto& pe : p)
            if (pe.first >= 0 && pe.second >= 0)
                ++nhits;
        return nhits;
    }

    void dumpHits(const std::vector<Hit>& vhit)
    {
        const char* tname[] = {
            "DT",
            "CSC",
            "RPC",
            "GEM"            
        };

        for (uint ihit = 0; ihit < vhit.size(); ++ihit)
        {
            const Hit& hit = vhit.at(ihit);
            std::cout << "Hit "           << ihit
                      << " , type : "       << tname[hit.type] << "[" << hit.type << "]"
                      << " , station : "    << hit.station
                      << " , ring : "       << hit.ring
                      << " , sector : "     << hit.sector
                      << " , emtf_theta : " << hit.emtf_theta
                      << " , emtf_phi : "   << hit.emtf_phi
                      << std::endl;
        }
    }
}

#endif