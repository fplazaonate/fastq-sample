#ifndef SETTINGS_HH
#define SETTINGS_HH

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

struct Settings
{
	std::vector<std::string> fastq_files;
	std::string output_file;
	size_t target_num_reads;
	size_t target_num_bases;
};

Settings get_settings(int argc, char* argv[]);
#endif // SETTINGS_HH
