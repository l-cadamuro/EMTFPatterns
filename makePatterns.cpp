#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <map>
#include "CSCPatternFormer.h"
#include "ThetaPhiSegmentation.h"
#include "Hit.h"
#include "TreeToHit.h"
#include "PatternUtils.h"
#include "PatternLogger.h"
#include "PhaseSpace.h"
#include "MuonTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TVector2.h"
#include "IOUtils.h"

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

// c++ -lm -o makePatterns.exe src/*.cc makePatterns.cpp `root-config --glibs --cflags` -I interface/ 

int main()
{
    // FIXME: stuff to overload from command line / config
    std::string inputFileList = "inputFiles/SingleMu_PU0.txt";
    unsigned int maxEvts = -1; // -1 for all
    float min_gen_mu_pt = 5.0;

    // -----------------------------------------------

    cout << "... execution starting" << endl;

    // open the files and create the tree
    TChain ch ("ntupler/tree");
    // ch.Add("testData/ntuple_0_SingleMuon_PU0.root");
    IOUtils::appendFromFileList(&ch, inputFileList);
    
    MuonTree mt (&ch);

    // define the detector segmentation to build patterns
    // each station can be confired separately (0 -- 4) in bins of theta and phi
    // indexed by (idxStation - 1)

    ThetaPhiSegmentation theta_phi_seg;
    // theta_phi_seg.bins_CSC_theta.at(0).setBins(33, 0, 99);
    // theta_phi_seg.bins_CSC_theta.at(1).setBins(33, 0, 99);
    // theta_phi_seg.bins_CSC_theta.at(2).setBins(33, 0, 99);
    // theta_phi_seg.bins_CSC_theta.at(3).setBins(33, 0, 99);

    // theta_phi_seg.bins_CSC_phi.at(0).setBins(33, 0, 5016);
    // theta_phi_seg.bins_CSC_phi.at(1).setBins(33, 0, 5016);
    // theta_phi_seg.bins_CSC_phi.at(2).setBins(33, 0, 5016);
    // theta_phi_seg.bins_CSC_phi.at(3).setBins(33, 0, 5016);

    // dummy segmentation to check that nbins converges
    theta_phi_seg.bins_CSC_theta.at(0).setBins(3, 0, 99);
    theta_phi_seg.bins_CSC_theta.at(1).setBins(3, 0, 99);
    theta_phi_seg.bins_CSC_theta.at(2).setBins(3, 0, 99);
    theta_phi_seg.bins_CSC_theta.at(3).setBins(3, 0, 99);

    theta_phi_seg.bins_CSC_phi.at(0).setBins(3, 0, 5016);
    theta_phi_seg.bins_CSC_phi.at(1).setBins(3, 0, 5016);
    theta_phi_seg.bins_CSC_phi.at(2).setBins(3, 0, 5016);
    theta_phi_seg.bins_CSC_phi.at(3).setBins(3, 0, 5016);


    // instantiate the pattern creator
    // if using the EMTF coordinate system (default of CSCPatternFormer)
    // one instance is enough, as the output only depends on the geometry and the hits.
    // the geometry is the same for every sector
    // the hits instead must be divided in six collections, one per sector

    CSCPatternFormer csc_patt_former;
    csc_patt_former.setMinValidElements(3); // at least 3 hits in a pattern

    // what we need to record properties of the patterns
    std::array < PatternLogger<CSCPatternFormer::patt_size> , 6 > patt_loggers; // one per each sector

    // PatternLogger<CSCPatternFormer::patt_size>::debug_ = true;
    // for (auto& pl : patt_loggers)
    //     pl.setDebug(false);
    // patt_loggers.at(0).setDebug(false);

    PhaseSpace ps;
    ps.setUseOneOverPt(true);
    ps.ptBins().setBins(100, 0, 0.5);
    ps.etaBins().setBins(100, 1.2, 2.5);
    ps.phiBins().setBins(100, -TMath::Pi(), TMath::Pi());

    // define some control metrics for the pattern training
    std::array<vector<std::pair<int, int>>, 6> v_of_num_patterns;
    std::array<vector<std::pair<int, int>>, 6> v_of_num_pselems;

    cout << "... event loop starting" << endl;

    for (uint iEv = 0; true; ++iEv)
    {
        int got = mt.GetEntry(iEv);
        if (!got) break;
        if (maxEvts >= 0 && iEv >= maxEvts) break;

        if (iEv % 10000 == 0)
            cout << "...... processing event " << iEv << endl;

        // divide into 6 sectors
        std::array<HitCollection,        6> HitCollections;
        std::array<CSCPatternCollection, 6> PatternCollections;

        // check the gen particle properties
        float gen_pt  = mt.vp_pt->at(0);
        float gen_eta = mt.vp_eta->at(0);
        float gen_phi = mt.vp_phi->at(0);
        if (gen_pt < min_gen_mu_pt) continue;

        auto ps_elem = ps.getPhaseSpaceElement(gen_pt, gen_eta, gen_phi);

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

            patt_loggers.at(isec).log(cscpc, ps_elem);

            // for (auto& patt : cscpc)
            //     if (putl::nValidHits(patt) < 3)
            //         cout << "Too few valid hits " << putl::nValidHits(patt) << endl;

            // for printing the patterns
            // for (auto& patt : cscpc)
            //     cout << CSCPatternFormer::pattern_toString(patt) << endl;
        
            if (patt_loggers.at(isec).getNCalls() % 1000 == 0){
                v_of_num_patterns.at(isec).push_back(make_pair(patt_loggers.at(isec).getNCalls(), patt_loggers.at(isec).getNpatterns()));
                v_of_num_pselems .at(isec).push_back(make_pair(patt_loggers.at(isec).getNCalls(), patt_loggers.at(isec).getNphaseSpaceElems()));
            }
        }
    }

    cout << "... loop done" << endl;
    cout << "... I genenerated the following patterns for each sector" << endl;
    for (int i = 0; i < patt_loggers.size(); ++i)
        cout << "S" << i+1 << " " << patt_loggers.at(i).getNpatterns() << endl;

    // put ncalls to a file
    for (uint isec = 0; isec < patt_loggers.size(); ++isec){
        string oname = "num_patterns_sec";
        oname += to_string(isec+1);
        oname += ".txt";
        cout << "... saving num patterns of sector " << isec+1 << " into " << oname << endl;
        std::ofstream fout (oname);
        for (auto& el : v_of_num_patterns.at(isec)){
            // cout << el.first << " " << el.second << endl;
            fout << el.first << " " << el.second << endl;
        }
        fout.close();
    }

    // put ncalls to a file
    for (uint isec = 0; isec < patt_loggers.size(); ++isec){
        string oname = "num_phase_space_elems_sec";
        oname += to_string(isec+1);
        oname += ".txt";
        cout << "... saving num phase space elemts of sector " << isec+1 << " into " << oname << endl;
        std::ofstream fout (oname);
        for (auto& el : v_of_num_pselems.at(isec)){
            // cout << el.first << " " << el.second << endl;
            fout << el.first << " " << el.second << endl;
        }
        fout.close();
    }
}
