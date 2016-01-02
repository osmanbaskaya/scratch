### Requirements
- cmake (sudo apt-get install cmake)
- g++
- google test suite (for unit tests)

Tested on Ubuntu 14.04 and CentOS.


### How To Run?

```bash
git clone git@github.com:osmanbaskaya/scratch.git
cd scratch/sbg
make top-kmers-small.txt  # we have small.fastq.gz file.
```

### How about Unit Tests?

```bash
cd test
cmake CMakeLists.txt
make
./runTests
```

### Introduction

#### Reading kmers into the memory

Finding top kmers is difficult when kmer size is big (like 30, for instance). The root of the difficulty is to fit 4^30 different combinations of kmers into the memory. Obviously, there are different data structures/algorithms (HyperLogLog etc.) for this purpose. However, I did not use them. Firstly, I used unordered map for keep tracking observed kmers. It worked fine for small datasets. Then, I tried the code for the biggest file in ftp://ftp.1000genomes.ebi.ac.uk/vol1/ftp/phase3/data/HG01595/sequence_read/, 5.5GB fastq file. Then, after using 30GB memory space, program has not passed 10% of the file yet. Then I made some experiments. I read 1M sequences and see the top kmers (it takes ~8GB memory). Then, I modified the code so that, in each epoch (passing 250K sequences), it removes (2 * epoch) or less occurred kmers. In other words, it cleans the memory for each epoch with linear manner. In the first epoch it removes 2 or less occurred kmers. In the second epoch it removes 4 or less and so on. I run the program on 1M sequences and got the same results. Then I run on 4M sequences -- got the same results. Cleaning also takes time so I changed my epoch definition; epoch is to pass 500K sequences and threshold now is 4 * epoch. I tried to pick threshold as small as possible so that at any moment of computing it takes ~4.8G memory space and it can be run on a laptop.

#### Finding the top-k kmers

I used min heap for finding the top kmers. It is good because it takes only O(k) memory space where k is the number of kmers we want to see. It works that way: While iterating over unordered map, if the top element in the heap (minimum) smaller than the current element in the unordered map then pop it (O(1)) and push the current element (O(log(k)). If it's smaller than the top, we do not need it! Skip it.


### Speed & Memory
```
CPU MHz:               1995.085  # a bit slow machine
```

Program processes 4M sequences (i.e., 16M fastq lines) in ~703 seconds with 1 CPU (and 1 thread). In other words, 175 seconds for each 1M sequences. In that time, it takes 4.8GB memory. I did not use any multiprocessing or multithreading, although it's possible. You can create a class whose base class is Thread. Each of instance of this class has *own* unordered map. Also, it's important to divide the work to these threads. Since the lines are ordered (sequences are not independent) we can't simply distribute lines into threads by round-robin fashion. Better is to divide the file into threads. At the end of the computation, main thread needs to traverse onto all unordered maps and create the final heap. I did not try this because (1) I am not fluent in C++, (2) even 5.5GB file takes 3.5 hours. I believe it is okay for an assignment. There is a tradeoff between memory and speed. You can clean the occurrence map more often and you can use ~2GB memory but this increases the execution time (2 times more cleaning).


#### Assumption

- Program supports different kmer sizes less than 91 (Sequence size is 90 in fastq formatted file).
- Threshold to clean the occurrence map (where kmers are kept) increased by each epoch, although it's really small. I assume that observed kmers in the beginning of the document do not totally different than observed kmers at the end. The smaller the kmer size, safer this assumption is. However, there is a chance to miss kmers especially very long kmer size. I tried 1M sequence at the beginning and 1M at the end and program with threshold returned exact same answer, so I believe threshold approach is pretty useful.
- Another assumption is that sequences are continuous. That is why I concatenate remaining nucleotids (kmer_size - 1 many nucleotids) with the current sequence.

```cpp
void KmerAnalyzer::extract_kmers_and_add(const string & previous_line, const string & current_line) {
    string kmer;
    string sequence;
    // Construct resultant string from the previous and current sequence.
    if (previous_line.length() >= kmer_size)
        sequence = previous_line.substr(sequence_size - kmer_size + 1, kmer_size-1) + current_line;
    else
        sequence = current_line;

    // cerr << "Previous:" << previous_line << endl;
    // cerr << "Concat:  " << sequence << endl;

    int end = sequence.size() - kmer_size;
    for (int i=0; i <= end; i++){
        kmer = sequence.substr(i, kmer_size);
        ++occurrence_map[kmer];
    }
}
```

### References
- http://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/
- http://askubuntu.com/questions/61408/what-is-a-command-to-compile-and-run-c-programs
- https://codeconnect.wordpress.com/2013/09/0/max-min-heap-using-c-stl/
- http://stackoverflow.com/questions/1842941/translating-python-dictionary-to-c
- http://www.cprogramming.com/tutorial/lesson14.html


### Note
I have not written any code in C++ before.
