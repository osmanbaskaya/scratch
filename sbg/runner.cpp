#include "kmer_analyzer.h"


int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage:\nkmers.out FILENAME KMER_SIZE NUM_TOP_KMERS\n";
    }
    const char * filename = argv[1];
    const int kmer_size = atoi(argv[2]);
    const int num_top_kmers = atoi(argv[3]);

    KmerAnalyzer analyzer(filename, kmer_size);
    analyzer.print_top_kmers(num_top_kmers);
    return 0;
}
