#ifndef FASTQ_RANDOM_SAMPLER_HH
#define FASTQ_RANDOM_SAMPLER_HH

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

#include <vector>
#include <string>
#include <memory>
#include "FastqEntry.hh"

class FastqRandomSampler
{
    public:
        virtual std::vector<FastqEntry> sample(const std::vector<std::string>& fastq_files) = 0;
        virtual ~FastqRandomSampler();
};

inline FastqRandomSampler::~FastqRandomSampler()
{
}

class NumReadsRandomSampler : public FastqRandomSampler
{
    public:
        NumReadsRandomSampler(const size_t target_num_reads, const int seed);
        std::vector<FastqEntry> sample(const std::vector<std::string>& fastq_files);
    private:
        const size_t target_num_reads_;
        const int seed_;
};

inline NumReadsRandomSampler::NumReadsRandomSampler(const size_t target_num_reads, const int seed)
    : target_num_reads_(target_num_reads), seed_(seed)
{
}

class NumBasesRandomSampler : public FastqRandomSampler
{
    public:
        NumBasesRandomSampler(const size_t target_num_bases, const int seed);
        std::vector<FastqEntry> sample(const std::vector<std::string>& fastq_files);
    private:
        const size_t target_num_bases_;
        const int seed_;
};

inline NumBasesRandomSampler::NumBasesRandomSampler(const size_t target_num_bases, const int seed)
    : target_num_bases_(target_num_bases), seed_(seed)
{
}

class ProportionRandomSampler : public FastqRandomSampler
{
    public:
        ProportionRandomSampler(const double target_proportion, const int seed);
        std::vector<FastqEntry> sample(const std::vector<std::string>& fastq_files);
    private:
        const double target_proportion_;
        const int seed_;
};

inline ProportionRandomSampler::ProportionRandomSampler(const double target_proportion, const int seed)
    : target_proportion_(target_proportion), seed_(seed)
{
}

class FastqRandomSamplerFactory
{
    public:
        static std::auto_ptr<FastqRandomSampler> create_sampler(
                const size_t target_num_reads,
                const size_t target_num_bases,
                const double target_proportion,
                const int seed);
    private:
        static const char MISSING_TARGET_ERR_MSG[];
        static const char MULTIPLE_TARGET_ERR_MSG[];
};

#endif // FASTQ_RANDOM_SAMPLER_HH
