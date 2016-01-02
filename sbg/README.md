### Requirements
- cmake (sudo apt-get install cmake)
- g++
- google test suite (for unit tests)


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

Finding top kmers is difficult when kmer size is big (like 30, for instance). The root of the difficulty is to fit 4^30 different combinations of kmers into the memory. Obviously, there are different data structures for this purpose. However, I did not use them. Firstly, I used unordered map for keep tracking observed kmers. It worked fine for small datasets. Then, I tried the code for the biggest file in ftp://ftp.1000genomes.ebi.ac.uk/vol1/ftp/phase3/data/HG01595/sequence_read/, 5.5GB fastq file. Then, after using 30GB memory space, program has not passed 10% of the file yet. Then I made some experiments. I read 1M sequences and see the top kmers (it takes 4GB memory). Then, I modified the code so that, in each epoch (passing 250K sequences), it removes (2 * epoch) or less occurred kmers. In other words, it cleans the memory for each epoch with linear manner. In the first epoch it removes 2 or less occurred kmers. In the second epoch it removes 4 or less and so on. I run the program on 1M sequences and got the same results. Then I run on 4M sequences -- got the same results. Cleaning also takes time so I changed my epoch definition; epoch is to pass 500K sequences and threshold now is 4 * epoch. I tried to pick threshold as small as possible so that at any moment of computing it takes ~3G memory space and it can be run on laptop (even not a fancy one). 

#### Finding the top-k kmers

I used min heap for finding the top kmers. It is good because it takes only O(k) memory space where k is the number of kmers we want to see. It works that way: While iterating over unordered map, if the top element in the heap (minimum) smaller than the current element in the unordered map then pop it (O(1)) and push the current element (O(log(k)). If it's smaller than the top, we do not need it! Skip it.


#### Assumption





### References
- http://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/
- http://askubuntu.com/questions/61408/what-is-a-command-to-compile-and-run-c-programs
- https://codeconnect.wordpress.com/2013/09/0/max-min-heap-using-c-stl/
- http://stackoverflow.com/questions/1842941/translating-python-dictionary-to-c
- http://www.cprogramming.com/tutorial/lesson14.html
