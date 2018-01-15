#ifndef PHASESPACE_H
#define PHASESPACE_H

/*
** class  : PhaseSpace
** author : L. Cadamuro (UF)
** date   : 12/01/2018
** brief  : redefines a tuple of integers that represent the bins of the phase space
**          note: can use both pt and 1/pt, switch with a bool
*/

#include <array>
#include "Boundaries.h"

// enum class PhaseSpace{
//     pt    , // 0
//     eta   , // 1
//     phi   , // 2
//     NELEM   // 3
// };

class PhaseSpace {
    public:

        enum Coords {
                pt    , // 0
                eta   , // 1
                phi   , // 2
                NELEM , // 3
        };

        PhaseSpace(){use_one_over_pt_ = false;}
        ~PhaseSpace(){};

        void setUseOneOverPt (bool val) {use_one_over_pt_ = val;}

        Boundaries<float>& ptBins()  {return phase_space_bins.at(Coords::pt);}
        Boundaries<float>& etaBins() {return phase_space_bins.at(Coords::eta);}
        Boundaries<float>& phiBins() {return phase_space_bins.at(Coords::phi);}

        std::array<int, Coords::NELEM> getPhaseSpaceElement(float pt, float eta, float phi); // returns the phase space element

    private:
        std::array<Boundaries<float>, static_cast<size_t>( Coords::NELEM) > phase_space_bins;
        bool use_one_over_pt_;
};

typedef std::array<int, PhaseSpace::Coords::NELEM> PhaseSpaceElement ; // indexed as the PhaseSpace elements

#endif