#ifndef FASTQ_WRITER
#define FASTQ_WRITER

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
#include <vector>
#include <fstream>
#include "FastqEntry.hh"

class FastqWriter
{
	public:
		FastqWriter(const std::string& fastq_file);
		~FastqWriter();
		void write(const std::vector<FastqEntry>& fastq_entries);
		void write(const std::vector<FastqEntry>& fastq_entries, const std::vector<size_t>& indexes);
		void write(const FastqEntry& fastq_entry);
	private:
		const std::string fastq_file_;
		std::ofstream ofs_;
};

#endif //FASTQ_WRITER
