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
        void setLogNCalls  (bool value){log_ncalls_    = value;}

        long int getNCalls () const;

        void log(const Pattern<S>& patt, const PhaseSpaceElement& ps);
        void log(const PatternCollection<S>& vpatt, const PhaseSpaceElement& ps);

        bool contains_pattern(Pattern<S> key) {return (map_phasespace_.find(key) != map_phasespace_.end()); }
        bool contains_phaseSpaceElement(PhaseSpaceElement key) {return (map_patterns_.find(key) != map_patterns_.end()); }

        int getNpatterns() const {return map_phasespace_.size();}
        int getNphaseSpaceElems() const {return map_patterns_.size();}

        // static bool debug_;
        // static void setDebug(bool val) {debug_ = val;}
        bool debug_ = false;
        void setDebug(bool val) {debug_ = val;}

    private:

        void logNCalls() {++ncalls_;};


        bool store_evt_num_   = false;
        bool log_ncalls_      = true;
        long int ncalls_      = 0; 
        
        bool logged_this_evt_ = false; // in case I call log() on a vector of patterns, I need to update the log count only once


        std::vector<unsigned int> v_evts_;

        std::map<Pattern<S> , std::vector<PhaseSpaceElement>> map_phasespace_; // pattern --> vector of phase space elements
        std::map<PhaseSpaceElement , std::vector<Pattern<S>>> map_patterns_;   // phase space element --> vector of patterns

};

// -----------------------------------------------------------------------------------------

// template <size_t S>
// bool PatternLogger<S>::debug_ = false;

template <size_t S>
PatternLogger<S>::PatternLogger()
{
    // store_evt_num_ = false;
    // log_ncalls_    = false;
    // debug_         = false;
}

template <size_t S>
PatternLogger<S>::~PatternLogger()
{}

template <size_t S>
long int PatternLogger<S>::getNCalls () const
{
    if (!log_ncalls_)
        std::cout << "[WARNING] PatternLogger : requesting getNCalls(), but log of nCalls was disabled" << std::endl;
    return ncalls_;
}

template <size_t S>
void PatternLogger<S>::log(const PatternCollection<S>& vpatt, const PhaseSpaceElement& ps)
{
    // log nevents only once per event
    logNCalls();
    logged_this_evt_ = true; // will inhibit logNCalls() inside log()
    
    for (auto& p : vpatt)
        log(p, ps);

    logged_this_evt_ = false; // re-enable

}

// FIXME: I should use the log() call by vector as the default
// much easier and more efficient for logging by phase space

template <size_t S>
void PatternLogger<S>::log(const Pattern<S>& patt, const PhaseSpaceElement& ps)
{
    if (debug_) std::cout << "[DEBUG] PatternLogger : logging pattern " << PatternFormerBase<S>::pattern_toString(patt) << std::endl;
    if (debug_) std::cout << "[DEBUG] PatternLogger : the initial num of patterns is " << getNpatterns() << std::endl;
 
    if (log_ncalls_ && !logged_this_evt_)
        logNCalls();

    // --------------------------- log the pattern --> phase space map

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
        found->second.push_back(ps); // FIXME: need to remove ps values already stored
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... new size " << getNpatterns() << std::endl;
    }

    if (debug_) std::cout << "[DEBUG] PatternLogger : ... the new number of patterns is " << getNpatterns() << std::endl;



    // --------------------------- log the phase space --> pattern map

    auto found2 = map_patterns_.find(ps);
    if (found2 == map_patterns_.end()) // not yet stored
    {
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... is a NEW phase space element, initial size " << getNphaseSpaceElems() << std::endl;
        std::vector<Pattern<S>> vpatt;
        vpatt.push_back(patt);
        map_patterns_[ps] = vpatt;
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... element inserted, is the key in the map? " << (map_patterns_.find(ps) != map_patterns_.end()) << std::endl;
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... new size " << getNphaseSpaceElems() << std::endl;
    }
    else // already existing
    {
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... is an existing pattern, initial size " << getNphaseSpaceElems() << std::endl;
        found2->second.push_back(patt); // FIXME: need to remove patterns already stored
        if (debug_) std::cout << "[DEBUG] PatternLogger : ... new size " << getNphaseSpaceElems() << std::endl;
    }

    if (debug_) std::cout << "[DEBUG] PatternLogger : ... the new number of patterns is " << getNphaseSpaceElems() << std::endl;


}

#endif