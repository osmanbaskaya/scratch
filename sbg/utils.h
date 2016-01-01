#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include <string>

using namespace std;

class Kmer
{
    public:
        int occurrence;
        string label;
        Kmer (string, int);
};


#endif // __UTILS_H_INCLUDED__
