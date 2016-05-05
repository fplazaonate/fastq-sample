#ifndef FASTQ_SEQUENCE_HH
#define FASTQ_SEQUENCE_HH

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

#include <string>
#include <iostream>

struct FastqEntry
{
    static const size_t MAX_SEQ_LEN = 400;
    std::string id;
    std::string seq;
    std::string quals;
};

std::ostream& operator<<(std::ostream& os, const FastqEntry& fastq_entry);

#endif //FASTQ_SEQUENCE_HH
