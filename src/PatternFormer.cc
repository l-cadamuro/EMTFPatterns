#include "PatternUtils.h"

// given a set of hits as input, arbitrate them, resolve ambiguities, and set the pattern_ member variable
void PatternUtils::CSCPattern::formPattern(std::vector<hit>& vhit)
{
    // FIXME: TO DO
    pattern_.at(0) = {1,1};
    pattern_.at(1) = {2,2};
    pattern_.at(2) = {3,3};
    pattern_.at(3) = {4,4};
}