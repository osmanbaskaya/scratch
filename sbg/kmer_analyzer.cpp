#include "kmer_analyzer.h"

KmerAnalyzer::KmerAnalyzer(const char * fn, const int size): filename(fn), kmer_size(size) {
    is_loaded = false;
}

priority_queue<Kmer, std::vector<Kmer>, Compare> KmerAnalyzer::find_top_kmers(const int num_top_kmers) {
    priority_queue<Kmer, std::vector<Kmer>, Compare> min_heap;
    for (const auto & element: occurrence_map) {
        if (min_heap.size() < num_top_kmers) {
            min_heap.push(Kmer(element.first, element.second));
        }
        else {
            if (min_heap.top().occurrence < element.second) {
                min_heap.pop();  // remove the minimum
                min_heap.push(Kmer(element.first, element.second));
            }
        }
    }
    return min_heap;
}


void KmerAnalyzer::extract_kmers_and_add(const string & sequence) {
    string kmer;
    int end = sequence.size() - kmer_size;
    for (int i=0; i < end; i++){
        kmer = sequence.substr(i, kmer_size);
        ++occurrence_map[kmer];
    }
}

void KmerAnalyzer::load_kmers() {
    string line;
    ifstream input_file (filename);
    int line_number = 0;
    if (input_file.is_open())
    {
        while ( getline (input_file,line) )
        {
            line_number++;
            // read only the sequence rows.
            if (line_number % 4 == 2) {
                extract_kmers_and_add(line);
            }
            if (line_number % 12 == 0) {
                cerr << line_number / 4 << " lines readed" << "\n";
            }
        }
        input_file.close();
        is_loaded = true;
    }
    else cerr << "Unable to open file"; 
}

void KmerAnalyzer::print_top_kmers(int num_top_kmers) {
    if (!is_loaded) {
        load_kmers();
    }

    priority_queue<Kmer, std::vector<Kmer>, Compare> min_heap = find_top_kmers(num_top_kmers);

    while (!min_heap.empty()) {
        Kmer first = min_heap.top();
        cout << first.occurrence << "\t" << first.label << "\n";
        min_heap.pop();
    }
}

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
