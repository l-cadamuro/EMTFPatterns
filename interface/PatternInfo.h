#ifndef PATTERNINFO_H
#define PATTERNINFO_H

/*
** class  : PatternInfo
** author : L. Cadamuro (UF)
** date   : 15/01/2018
** brief  : A class that stores several types of information about a pattern
**          The information to be stored can be configured globally via static variables
*/

#include "Pattern.h"

template <size_t S>
class PatternInfo {
    
    public:
        PatternInfo(){};
        ~PatternInfo(){};

        static bool save_evts_;
    
    // private:

};

bool PatternInfo::save_evts_ = false;

#endif