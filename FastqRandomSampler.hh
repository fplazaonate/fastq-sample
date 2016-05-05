#ifndef FASTQ_RANDOM_SAMPLER_HH
#define FASTQ_RANDOM_SAMPLER_HH

#include <vector>
#include <string>
#include "FastqEntry.hh"

class FastqRandomSampler
{
    public:
        static std::vector<FastqEntry> num_reads(const std::vector<std::string>& fastq_files, const size_t target_num_reads);
        static std::vector<FastqEntry> num_bases(const std::vector<std::string>& fastq_files, const size_t target_num_bases);
};

#endif // FASTQ_RANDOM_SAMPLER_HH
