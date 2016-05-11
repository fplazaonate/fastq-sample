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

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "Settings.hh"
#include "FastqRandomSampler.hh"
#include "FastqWriter.hh"

int main(int argc, char *argv[])
{
    try
    {
        const Settings& settings = get_settings(argc, argv);

        std::auto_ptr<FastqRandomSampler> fastq_random_sampler =
            FastqRandomSamplerFactory::create_sampler(
                    settings.target_num_reads,
                    settings.target_num_bases);

        const std::vector<FastqEntry>& fastq_entries =
            fastq_random_sampler->sample(settings.fastq_files);

        FastqWriter fastq_writer(settings.output_file);
        fastq_writer.write(fastq_entries);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::exit(-1);
    }

    return 0;
}
