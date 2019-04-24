/*
 * Copyright 2016 Enterome
 *
 * This file is part of fastq-sample
 *
 * fastq-sample is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * fastq-sample is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fastq-sample. If not, see <http://www.gnu.org/licenses/>.
 */

#include "FastqRandomSampler.hh"
#include "FastqMultiReader.hh"
#include "randomc.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <stdexcept>

std::vector<FastqEntry> NumReadsRandomSampler::sample(const std::vector<std::string>& fastq_files)
{
    std::vector<FastqEntry> fastq_entries;

    // Fill reservoir
    FastqMultiReader fastq_multi_reader(fastq_files);
    fastq_multi_reader.next_chunk(fastq_entries, target_num_reads_);

    if (fastq_entries.size() < target_num_reads_)
    {
        std::cerr << "warning: only " << fastq_entries.size() << " reads available in input files." << std::endl;
    }
    else
    {
        // Perform reservoir sampling
        CRandomMersenne mt(seed_);
        FastqEntry fastq_entry;
        size_t n = target_num_reads_;
        while (fastq_multi_reader.next_entry(fastq_entry))
        {
            const size_t j = mt.IRandomX(0,n);
            if (j < target_num_reads_)
            {
                fastq_entries[j] = fastq_entry;
            }
            ++n;
        }
    }

    return fastq_entries;
}

std::vector<FastqEntry> NumBasesRandomSampler::sample(const std::vector<std::string>& fastq_files)
{
    std::vector<FastqEntry> fastq_entries;
    CRandomMersenne mt(seed_);

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
    while (cur_num_entries < fastq_entries.size() && cur_num_bases < target_num_bases_)
    {
        const FastqEntry& cur_fastq_entry = fastq_entries[fastq_entries_indexes[cur_num_entries]];
        cur_num_bases += cur_fastq_entry.seq.size();
        ++cur_num_entries;
    }
    const size_t final_num_entries = cur_num_entries;
    fastq_entries_indexes.resize(final_num_entries);

    if (cur_num_bases < target_num_bases_)
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

std::vector<FastqEntry> ProportionRandomSampler::sample(const std::vector<std::string>& fastq_files)
{
    FastqMultiReader fastq_multi_reader(fastq_files);
    std::vector<FastqEntry> fastq_entries;

    if (target_proportion_ == 1.0)
    {
        fastq_multi_reader.all_entries(fastq_entries);
    }
    else
    {
        CRandomMersenne mt(seed_);
        FastqEntry fastq_entry;
        while (fastq_multi_reader.next_entry(fastq_entry))
        {
            if (mt.Random() <= target_proportion_)
                fastq_entries.push_back(fastq_entry);
        }
    }

    return fastq_entries;
}

std::auto_ptr<FastqRandomSampler> FastqRandomSamplerFactory::create_sampler(
        const size_t target_num_reads,
        const size_t target_num_bases,
        const double target_proportion, 
        const int seed)
{
    FastqRandomSampler* fastq_random_sampler = NULL;

    if (target_num_reads != 0)
    {
        fastq_random_sampler = new NumReadsRandomSampler(target_num_reads, seed);
    }
    else if (target_num_bases != 0)
    {
        if (fastq_random_sampler != NULL)
        {
            throw std::invalid_argument(MULTIPLE_TARGET_ERR_MSG);
        }
        fastq_random_sampler = new NumBasesRandomSampler(target_num_bases, seed);
    }
    else if (target_proportion != 0.0)
    {
        if (fastq_random_sampler != NULL)
        {
            throw std::invalid_argument(MULTIPLE_TARGET_ERR_MSG);
        }
        fastq_random_sampler = new ProportionRandomSampler(target_proportion, seed);
    }

    if (fastq_random_sampler == NULL)
    {
        throw std::invalid_argument(MISSING_TARGET_ERR_MSG);
    }

    return std::auto_ptr<FastqRandomSampler>(fastq_random_sampler);
}

const char FastqRandomSamplerFactory::MISSING_TARGET_ERR_MSG[] =
"error: missing --target-xxx parameter";

const char FastqRandomSamplerFactory::MULTIPLE_TARGET_ERR_MSG[] =
"error: multiple --target-xxx parameters used";
