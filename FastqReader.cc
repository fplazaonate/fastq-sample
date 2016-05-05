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

#include "FastqReader.hh"

FastqReader::FastqReader(const std::string& filepath)
    : filepath_(filepath), filestream_(filepath_.c_str(), std::ios_base::in), line_()
{
    line_.reserve(10000);
}

FastqReader::~FastqReader()
{
    filestream_.close();
}

bool FastqReader::next_entry(FastqEntry& fastq_entry)
{
    if (!filestream_.good())
    {
        return false;
    }

    // Step 1: read entry header
    std::getline(filestream_, line_);
    if (line_.empty())
    {
        // Sometimes FASTQ files have empty last line_s
        filestream_.setstate(std::ios::eofbit);
        return false;
    }

    if (line_[0] != '@')
    {
        // TODO: had error msg
        filestream_.setstate(std::ios::failbit);
        return false;
    }
    fastq_entry.id = line_.substr(1);

    // Step 2: read entry sequence
    std::getline(filestream_, fastq_entry.seq);
    if (fastq_entry.seq.empty())
    {
        // TODO: had error msg
        filestream_.setstate(std::ios::failbit);
        return false;
    }

    // Step 3: read quals separator
    std::getline(filestream_, line_);
    if (line_.empty() || line_[0] != '+')
    {
        // TODO: had error msg
        filestream_.setstate(std::ios::failbit);
        return false;
    }

    // Step 4: read quals
    std::getline(filestream_, fastq_entry.quals);
    if (fastq_entry.quals.empty())
    {
        // TODO: had error msg
        filestream_.setstate(std::ios::failbit);
        return false;
    }
    return true;
}
