#ifndef PATTERNLOGGER_H
#define PATTERNLOGGER_H

/*
** class  : PatternLogger
** author : L. Cadamuro (UF)
** date   : 12/01/2018
** brief  : a wrapper of a map to associate, to every bin of the phase space in study, all the patterns found
**          the class is templated on the size of the pattern to be stored
*/

#include <map>
#include <vector>
#include "Pattern.h"
#include "Boundaries.h"
#include "PhaseSpace.h"
#include "PatternFormerBase.h"

/* FIXME: questo logger deve dare accesso a 
- chiave pattenr --> pt, eta, phi, ...
- chiave phase space (pt, eta, phi, ..) --> pattenr
- deve essere mergeable (i.e., combino piu sectors in un unico Logger) ==> possiblita di skippare alcune chiavi tipo phi
- deve poter opzionalmente salvare gli eventi che entrano in un certo patterne phase space (per debug)
- deve poter opzionalmente contare gli eventi che entrano per una certa chiave
*/

template <size_t S>
class PatternLogger {
    
    public:
        PatternLogger();
        ~PatternLogger();

        void setStoreEvtNum(bool value){store_evt_num_ = value;}
        void setCountEvts  (bool value){count_evts_    = value;}

        void log(const Pattern<S>& patt, const PhaseSpaceElement& ps);
        void log(const PatternCollection<S>& vpatt, const PhaseSpaceElement& ps) {for (auto& p : vpatt) log(p, ps); };

        bool contains_pattern(Pattern<S> key) {return (map_phasespace_.find(key) != map_phasespace_.end()); }

        int getNpatterns() const {return map_phasespace_.size();}

        // static bool debug_;
        // static void setDebug(bool val) {debug_ = val;}
        bool debug_;
        void setDebug(bool val) {debug_ = val;}

    private:

        bool store_evt_num_;
        bool count_evts_;
        
        std::vector<unsigned int> v_evts_;

        std::map<Pattern<S> , std::vector<PhaseSpaceElement>> map_phasespace_; // pattern --> vector of phase space elements

};

// -----------------------------------------------------------------------------------------

// template <size_t S>
// bool PatternLogger<S>::debug_ = false;

template <size_t S>
PatternLogger<S>::PatternLogger()
{
    store_evt_num_ = false;
    count_evts_    = false;
}

template <size_t S>
PatternLogger<S>::~PatternLogger()
{}

template <size_t S>
void PatternLogger<S>::log(const Pattern<S>& patt, const PhaseSpaceElement& ps)
{
    if (debug_) std::cout << "[DEBUG] PatternLogger : logging pattern " << PatternFormerBase<S>::pattern_toString(patt) << std::endl;
    if (debug_) std::cout << "[DEBUG] PatternLogger : the initial num of patterns is " << getNpatterns() << std::endl;
    
    auto found = map_phasespace_.find(patt);
    if (found == map_phasespace_.end()) // not yet stored
    {
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... is a NEW pattern, initial size " << getNpatterns() << std::endl;
        std::vector<PhaseSpaceElement> vps;
        vps.push_back(ps);
        map_phasespace_[patt] = vps;
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... element inserted, is the key in the map? " << (map_phasespace_.find(patt) != map_phasespace_.end()) << std::endl;
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... new size " << getNpatterns() << std::endl;
    }
    else // already existing
    {
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... is an existing pattern, initial size " << getNpatterns() << std::endl;
        map_phasespace_[patt].push_back(ps);
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... new size " << getNpatterns() << std::endl;
    }

    if (debug_) std::cout << "[DEBUG] PatternLogger : ... the new number of patterns is " << getNpatterns() << std::endl;

}

#endif