#include "ReadsRandomSampler.hh"
#include "FastqMultiReader.hh"
#include <algorithm>
#include <ctime>
#include <iostream>
#include "randomc.h"

std::vector<FastqEntry> ReadsRandomSampler::num_reads(const std::vector<std::string>& fastq_files, const size_t target_num_reads)
{
    std::vector<FastqEntry> fastq_entries;

    // Fill reservoir
    FastqMultiReader fastq_multi_reader(fastq_files);
    fastq_multi_reader.next_chunk(fastq_entries, target_num_reads);

    if (fastq_entries.size() < target_num_reads)
    {
        std::cerr << "warning: only " << fastq_entries.size() << " reads available in input files." << std::endl;
    }
    else
    {
        // Perform reservoir sampling
        CRandomMersenne mt(std::time(0));
        FastqEntry fastq_entry;
        size_t n = target_num_reads;
        while (fastq_multi_reader.next_entry(fastq_entry))
        {
            const size_t j = mt.IRandomX(0,n);
            if (j < target_num_reads)
            {
                fastq_entries[j] = fastq_entry;
            }
            ++n;
        }
    }

    return fastq_entries;
}

std::vector<FastqEntry> ReadsRandomSampler::num_bases(const std::vector<std::string>& fastq_files, const size_t target_num_bases)
{
    std::vector<FastqEntry> fastq_entries;
    CRandomMersenne mt(std::time(0));

    // Read and shuffle all reads
    FastqMultiReader fastq_multi_reader(fastq_files);
    fastq_multi_reader.all_entries(fastq_entries);

    std::vector<size_t> fastq_entries_indexes(fastq_entries.size());
    for (size_t i = 0; i < fastq_entries.size(); ++i)
    {
        fastq_entries_indexes[i] = i;
    }

    std::random_shuffle(fastq_entries_indexes.begin(), fastq_entries_indexes.end(), mt);

    // Pick reads until target number of bases is reached
    size_t cur_num_bases = 0;
    size_t cur_num_entries = 0;
    while (cur_num_entries < fastq_entries.size() && cur_num_bases < target_num_bases)
    {
        const FastqEntry& cur_fastq_entry = fastq_entries[fastq_entries_indexes[cur_num_entries]];
        cur_num_bases += cur_fastq_entry.seq.size();
        ++cur_num_entries;
    }
    const size_t final_num_entries = cur_num_entries;
    fastq_entries_indexes.resize(final_num_entries);

    if (cur_num_bases < target_num_bases)
    {
        std::cerr << "warning: only " << cur_num_bases << " bases available in input files." << std::endl;
    }
    else
    {
        std::sort(fastq_entries_indexes.begin(), fastq_entries_indexes.end());
        for (size_t i = 0; i < final_num_entries; ++i)
        {
            fastq_entries[i] = fastq_entries[fastq_entries_indexes[i]];
        }
        fastq_entries.resize(final_num_entries);
    }

    return fastq_entries;
}

