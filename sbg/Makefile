KMER_SIZE = 30
kmers.out: kmers.cpp
	g++ -std=c++11 kmers.cpp -o $@

top-kmers-%: kmers.out %.fastq
	./$< $*.fastq ${KMER_SIZE} | sort -nr > $@
	cat $@
