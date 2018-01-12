#ifndef HIT_H
#define HIT_H

/*
** class  : Hit
** author : L. Cadamuro (UF)
** brief  : data that represent a hit
** notes  : Hit member names are defined to have a one-to-one correspondence with the flat ntuple used for the study
*/

#include <vector>

struct Hit {
    short   endcap;
    short   station;
    short   ring;
    short   sector;
    short   subsector;
    short   chamber;
    short   cscid;
    short   bx;
    short   type;
    short   neighbor;
    short   zonecode;
    short   zonehit;
    short   strip;
    short   wire;
    short   roll;
    short   pattern;
    short   quality;
    short   bend;
    short   time;
    short   fr;
    int     emtf_phi;
    int     emtf_theta;
    float   sim_phi;
    float   sim_theta;
    float   sim_eta;
    float   sim_r;
    float   sim_z;
    int     sim_tp1;
    int     sim_tp2;
};

typedef std::vector<Hit> HitCollection;


#endif