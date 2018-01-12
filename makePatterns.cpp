#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include "CSCPatternFormer.h"
#include "ThetaPhiSegmentation.h"
#include "Hit.h"
#include "TreeToHit.h"
#include "PatternUtils.h"
#include "MuonTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TVector2.h"

#include "TApplication.h"

#define DEBUG false

using namespace std;
namespace putl = PatternUtils;

// --- note on the sector geometry
// --- each sector is  81 degrees
// --- and is shifted by 60 degrees
// 1: -5.5    ..   75.5
// 2:  54.5   ..   135.5
// 3:  114.5  ..  -164.5
// 4:  174.5  ..  -104.5
// 5: -125.5  ..  -44.5
// 6: -65.5   ..   15.5

// c++ -lm -o makePatterns src/*.cc makePatterns_test.cpp `root-config --glibs --cflags` -I interface/

int main()
{
    cout << "... execution starting" << endl;

    // open the files and create the tree
    TChain ch ("ntupler/tree");
    ch.Add("testData/ntuple_0_SingleMuon_PU0.root");
    
    MuonTree mt (&ch);

    // define the detector segmentation to build patterns
    // each station can be confired separately (0 -- 4) in bins of theta and phi
    // indexed by (idxStation - 1)
    ThetaPhiSegmentation theta_phi_seg;
    theta_phi_seg.bins_CSC_theta.at(0).setBins(33, 0, 99);
    theta_phi_seg.bins_CSC_theta.at(1).setBins(33, 0, 99);
    theta_phi_seg.bins_CSC_theta.at(2).setBins(33, 0, 99);
    theta_phi_seg.bins_CSC_theta.at(3).setBins(33, 0, 99);

    theta_phi_seg.bins_CSC_phi.at(0).setBins(33, 0, 5016);
    theta_phi_seg.bins_CSC_phi.at(1).setBins(33, 0, 5016);
    theta_phi_seg.bins_CSC_phi.at(2).setBins(33, 0, 5016);
    theta_phi_seg.bins_CSC_phi.at(3).setBins(33, 0, 5016);

    // instantiate the pattern creator
    // if using the EMTF coordinate system (default of CSCPatternFormer)
    // one instance is enough, as the output only depends on the geometry and the hits.
    // the geometry is the same for every sector
    // the hits instead must be divided in six collections, one per sector

    CSCPatternFormer csc_patt_former;

    cout << "... event loop starting" << endl;

    for (uint iEv = 0; true; ++iEv)
    {
        int got = mt.GetEntry(iEv);
        if (!got) break;

        if (iEv % 10000 == 0)
            cout << "...... processing event " << iEv << endl;

        // divide into 6 sectors
        std::array<HitCollection,        6> HitCollections;
        std::array<CSCPatternCollection, 6> PatternCollections;

        // prepare the hits
        for (unsigned int ihit = 0; ihit < mt.vh_size; ++ihit){
            Hit h = TreeToHit::tree_to_hit(&mt, ihit);
            if (h.type != 1) continue;   // only CSC
            HitCollections.at(h.sector -1).push_back(h);
        }

        // compute the pattern of each sector, skipping those which will have no hits in input
        for (uint isec = 0; isec < HitCollections.size(); ++isec)
        {
            if (HitCollections.at(isec).empty()) continue;
            CSCPatternCollection cscpc = csc_patt_former.formPatterns(HitCollections.at(isec), theta_phi_seg);
            PatternCollections.at(isec) = cscpc;
        }
    }

    cout << "... loop done" << endl;
}
