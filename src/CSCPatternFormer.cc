#include "CSCPatternFormer.h"
#include "SpecialPatternElements.h"

// given a set of hits as input, produce all the possible patterns in output
// hits are associated an index according to the input detector geometry (bins of input coordinates to determine the PatternElement)

typedef std::vector<PatternElement<>> PatternElementCollection;

namespace sep = SpecialPatternElements;
using namespace std;

// a CSC pattern is formed by 4 pattern elements - one per each 
CSCPatternCollection CSCPatternFormer::formPatterns(const std::vector<Hit>& vhit, const DetectorSegmentationBase& segmentation)
{
    std::array<PatternElementCollection, 4> pe_hits; // S1, S2, S3, S4 : for every station list the valid hits by their index

    for (unsigned int ihit = 0; ihit < vhit.size(); ++ihit)
    {
        const Hit& hit = vhit.at(ihit);
        if (hit.type != (int) Subsystem::kCSC) continue; // CSC only
        int station = hit.station;
        auto pe = segmentation.getPatternElement(hit);
        if (std::find(pe_hits.at(station-1).begin(), pe_hits.at(station-1).end(), pe) == pe_hits.at(station-1).end())
            pe_hits.at(station-1).push_back(pe); // possibly multiple hits in the same pattern element
    }

    // if a hit is missing: introduce a dummy pattern
    for (unsigned int is = 0; is < pe_hits.size(); ++is)
        if (pe_hits.at(is).size() == 0)
            pe_hits.at(is).push_back(sep::missing_element_);

    unsigned int npattern = 1;
    for (unsigned int is = 0; is < pe_hits.size(); ++is)
        npattern *= pe_hits.at(is).size();


    // make all possible pattern_element combinations
    std::vector<Pattern<4>> patterns;
    patterns.reserve(npattern);
    for (unsigned int iS1 = 0; iS1 < pe_hits.at(0).size(); ++iS1)
        for (unsigned int iS2 = 0; iS2 < pe_hits.at(1).size(); ++iS2)
            for (unsigned int iS3 = 0; iS3 < pe_hits.at(2).size(); ++iS3)
                for (unsigned int iS4 = 0; iS4 < pe_hits.at(3).size(); ++iS4)
                {
                    int nvalidPE = (
                        static_cast<int>(sep::isValidPatternElement(pe_hits.at(0).at(iS1))) + 
                        static_cast<int>(sep::isValidPatternElement(pe_hits.at(1).at(iS2))) + 
                        static_cast<int>(sep::isValidPatternElement(pe_hits.at(2).at(iS3))) +
                        static_cast<int>(sep::isValidPatternElement(pe_hits.at(3).at(iS4)))
                    );
                    if (nvalidPE < 0 || nvalidPE > 4) cout << "OOOOOOOOO" << endl;
                    if (nvalidPE < min_valid_el_) continue;

                    patterns.emplace_back(Pattern<4> {{
                        pe_hits.at(0).at(iS1),
                        pe_hits.at(1).at(iS2),
                        pe_hits.at(2).at(iS3),
                        pe_hits.at(3).at(iS4)
                    }});
                }

    return patterns;
}