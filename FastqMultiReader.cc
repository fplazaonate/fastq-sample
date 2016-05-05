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

#include "FastqMultiReader.hh"

FastqMultiReader::FastqMultiReader(const std::vector<std::string>& fastq_files)
    : fastq_files_(fastq_files), cur_fastq_file_(fastq_files_.begin()), cur_fastq_reader_(NULL)
{
    if (cur_fastq_file_ != fastq_files_.end())
    {
        cur_fastq_reader_ = std::auto_ptr<FastqReader>(new FastqReader(*cur_fastq_file_));
    }
}
bool FastqMultiReader::next_entry(FastqEntry& fastq_entry)
{
    while (cur_fastq_file_ != fastq_files_.end())
    {
        if (cur_fastq_reader_->next_entry(fastq_entry))
        {
            return true;
        }

        ++cur_fastq_file_;
        if (cur_fastq_file_ != fastq_files_.end())
        {
            cur_fastq_reader_ = std::auto_ptr<FastqReader>(new FastqReader(*cur_fastq_file_));
        }
    }

    return false;
}

bool FastqMultiReader::next_chunk(std::vector<FastqEntry>& fastq_entries, const size_t chunk_size)
{
    fastq_entries.clear();

    if (cur_fastq_file_ == fastq_files_.end())
        return false;

    FastqEntry fastq_entry;
    fastq_entries.reserve(chunk_size);
    while (fastq_entries.size() < chunk_size && next_entry(fastq_entry))
    {
        fastq_entries.push_back(fastq_entry);
    }

    return !fastq_entries.empty();
}

bool FastqMultiReader::all_entries(std::vector<FastqEntry>& fastq_entries)
{
    fastq_entries.clear();

    std::vector<FastqEntry> chunk;
    while (next_chunk(chunk))
    {
        fastq_entries.insert(fastq_entries.end(), chunk.begin(), chunk.end());
    }

    return true;
}
