#ifndef BOUNDARIES_H
#define BOUNDARIES_H

/*
** class  : Boundaries
** author : L. Cadamuro (UF)
** brief  : an indexed range of quantitites (a la ROOT::TH1 bins)
** note   : - indexes are represented as int (safe cast from std::vector<T>::size_type) 
**          - first bin is 0, underflow is -1
*/

#include <vector>
#include <algorithm>

template <typename T>
class Boundaries{
    public:

        Boundaries(){};
        Boundaries(std::vector<T>& bins) {setBins(bins);}
        ~Boundaries(){};

        void setBins(std::vector<T>& bins);
        typename std::vector<T>::size_type size()  {return bins_.size();} // size of the member vector
        typename std::vector<T>::size_type nBins() {return size()-1;}     // -1 because these are the boundaries

        const std::vector<T>& getBins() const {return bins_;}

        int findBin (T value) const;

        void printVector (const std::vector<T>& bins) const;

    private:
        std::vector<T> bins_;
};

// ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ - ------ 

template <typename T>
void Boundaries<T>::setBins(std::vector<T>& bins)
{
    bins_ = bins;
    if (!is_sorted(bins_.begin(), bins_.end()))
    {
        std::cout << " ** Boundaries : [WARNING] : the following bins are not sorted " << std::endl; 
        printVector(bins_);
        std::cout << " ** going to sort them" << std::endl;
        std::sort(bins_.begin(), bins_.end());
    }
}

template <typename T>
void Boundaries<T>::printVector (const std::vector<T>& bins) const
{
    for (auto& val : bins)
        std::cout << val << " ";
    std::cout << std::endl;
}

template <typename T>
int Boundaries<T>::findBin (T value) const
{
    // vector is guaranteed to be sorted by setBins()
    // upper_bound returns the largest element iterator that is stricly greater than value
    // i.e. :  v = {1, 3, 5, 7}
    // int( upper_bound(x.begin(), x.end(), 0) - x.begin() ) ===> 0 
    // int( upper_bound(x.begin(), x.end(), 1) - x.begin() ) ===> 1 
    // int( upper_bound(x.begin(), x.end(), 2) - x.begin() ) ===> 1 
    // int( upper_bound(x.begin(), x.end(), 3) - x.begin() ) ===> 2 
    // int( upper_bound(x.begin(), x.end(), 4) - x.begin() ) ===> 2 
    
    auto upperbound = std::upper_bound(bins_.begin(), bins_.end(), value);

    // shift previous by -1 unit, so that:
    // -1: underflow
    //  0: first bin  (v.at(0))
    //  1: second bin (v.at(1))
    //  v.size() - 1 : overflow bin
    //      1 , 3 , 5 , 7      --> bins_.size() ==> 4   
    //  -1  | 0 | 1 | 2 | (3)  --> -1 is uflow, size() - 1 = nBins() is oflow

    // as a result, intervals are represented as asymmetric boundaries
    // {A, B, C, D}  ==> [A, B), [B, C), [C, D), [D, E)

    int ibin = (upperbound - bins_.begin()) - 1;
    return ibin;
}

#endif