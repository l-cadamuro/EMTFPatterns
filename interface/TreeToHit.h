#ifndef TREETOHIT_H
#define TREETOHIT_H

/*
** class  : TreeToHit
** author : L. Cadamuro (UF)
** brief  : utilities for interfacing the ROOT ntuples to the format needed to the patterns
*/

#include "Hit.h"
#include "MuonTree.h"

class TreeToHit
{
    public:
        TreeToHit();
        ~TreeToHit();
        static Hit tree_to_hit (MuonTree* mt, int ihit);
};

Hit TreeToHit::tree_to_hit (MuonTree* mt, int ihit)
{
    Hit h;
    h.endcap    = mt->vh_endcap->at(ihit);
    h.station   = mt->vh_station->at(ihit);
    h.ring      = mt->vh_ring->at(ihit);
    h.sector    = mt->vh_sector->at(ihit);
    h.subsector = mt->vh_subsector->at(ihit);
    h.chamber   = mt->vh_chamber->at(ihit);
    h.cscid     = mt->vh_cscid->at(ihit);
    h.bx        = mt->vh_bx->at(ihit);
    h.type      = mt->vh_type->at(ihit);
    h.neighbor  = mt->vh_neighbor->at(ihit);
    // h.zonecode  = mt->vh_zonecode->at(ihit);
    // h.zonehit   = mt->vh_zonehit->at(ihit);
    h.strip     = mt->vh_strip->at(ihit);
    h.wire      = mt->vh_wire->at(ihit);
    h.roll      = mt->vh_roll->at(ihit);
    h.pattern   = mt->vh_pattern->at(ihit);
    h.quality   = mt->vh_quality->at(ihit);
    h.bend      = mt->vh_bend->at(ihit);
    h.time      = mt->vh_time->at(ihit);
    h.fr        = mt->vh_fr->at(ihit);
    h.emtf_phi  = mt->vh_emtf_phi->at(ihit);
    h.emtf_theta= mt->vh_emtf_theta->at(ihit);
    h.sim_phi   = mt->vh_sim_phi->at(ihit);
    h.sim_theta = mt->vh_sim_theta->at(ihit);
    h.sim_eta   = mt->vh_sim_eta->at(ihit);
    h.sim_r     = mt->vh_sim_r->at(ihit);
    h.sim_z     = mt->vh_sim_z->at(ihit);
    h.sim_tp1   = mt->vh_sim_tp1->at(ihit);
    h.sim_tp2   = mt->vh_sim_tp2->at(ihit);
    return h;
}

#endif
