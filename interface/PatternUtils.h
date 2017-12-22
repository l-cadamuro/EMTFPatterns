#ifndef PATTERNUTILS_H
#define PATTERNUTILS_H

/*
** class  : PatternUtils
** author : L. Cadamuro (UF)
** brief  : utilities for building and booking EMTF patterns
** notes  : - a "PatternElement" is a combination of two values (first = theta and second = phi)
**          - a "Pattern" is a collection of an arbitrary (but fixed) number of "PatternElement"
*/

#include <utility>
#include <array>
#include <vector>

namespace PatternUtils {

    // ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - 

    template <typename T1 = int, typename T2 = int>           using PatternElement = std::pair<T1, T2> ;
    template <size_t S, typename T1 = int, typename T2 = int> using Pattern        = std::array<PatternElement<T1,T2>, S> ;

    // ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - 

    struct hit {
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

    // ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - 

    template <size_t S>
    class PatternFormerBase {
        public:
            PatternFormerBase(){};
            ~PatternFormerBase(){};
            virtual void formPattern(std::vector<hit>& vhit) = 0;
            Pattern<S> getPattern() const {return pattern_;}
        protected:
            Pattern<S> pattern_;
    };

    // ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - 

    // a pattern made only of CSCs hits
    class CSCPattern : public PatternFormerBase<4> {
        public:
            CSCPattern(){};
            ~CSCPattern(){};
            void formPattern(std::vector<hit>& vhit);
    };



}

#endif