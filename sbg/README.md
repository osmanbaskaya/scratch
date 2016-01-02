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
more to come



### References
- http://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/
- http://askubuntu.com/questions/61408/what-is-a-command-to-compile-and-run-c-programs
- https://codeconnect.wordpress.com/2013/09/0/max-min-heap-using-c-stl/
- http://stackoverflow.com/questions/1842941/translating-python-dictionary-to-c
- http://www.cprogramming.com/tutorial/lesson14.html
