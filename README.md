fastq-sample
===========
fastq-sample performs simple random sampling of reads from FASTQ files.

Sampling modes
-------------
3 modes are available:
*  random sampling of a target number of reads
*  random sampling of a target number of bases
*  random sampling of a target proportion of reads

Usage
-------------
*  `-f [ --fastq-files ] arg      `  input FASTQ files (use /dev/fd/0 for stdin)
*  `-o [ --output-file ] arg      `  output FASTQ file (use /dev/fd/1 for stdout)
*  `-r [ --target-num-reads ] arg `  number of reads to sample
*  `-b [ --target-num-bases ] arg `  number of bases to sample
*  `-p [ --target-proportion ] arg`  proportion of total reads to sample

Compilation requirements
-------------
- A C++ compiler (tested with gcc 4.4)
- [Boost C++ Libraries](http://www.boost.org)

