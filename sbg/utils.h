#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

using namespace std;

class Kmer
{
    public:
        int occurrence;
        string label;
        Kmer (string, int);
};


#endif // __UTILS_H__
