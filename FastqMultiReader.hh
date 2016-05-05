#ifndef FASTQ_MULTI_READER_HH
#define FASTQ_MULTI_READER_HH

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
#include "FastqReader.hh"

class FastqMultiReader
{
    public:
        FastqMultiReader(const std::vector<std::string>& fastq_files);
        bool next_entry(FastqEntry& fastq_entry);
        bool next_chunk(std::vector<FastqEntry>& fastq_entries, const size_t chunk_size = DEFAULT_CHUNK_SIZE);
        bool all_entries(std::vector<FastqEntry>& fastq_entries);

    private:
        static const size_t DEFAULT_CHUNK_SIZE = 100000;
        const std::vector<std::string> fastq_files_;
        std::vector<std::string>::const_iterator cur_fastq_file_;
        std::auto_ptr<FastqReader> cur_fastq_reader_;
};

#endif // FASTQ_MULTI_READER_HH
