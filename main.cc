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
        
        if (settings.target_num_bases != 0)
        {
            const std::vector<FastqEntry>& fastq_entries =
                FastqRandomSampler::num_bases(settings.fastq_files, settings.target_num_bases);

            FastqWriter fastq_writer(settings.output_file);
            fastq_writer.write(fastq_entries);
        }
        else if (settings.target_num_reads != 0)
        {
            const std::vector<FastqEntry>& fastq_entries =
                FastqRandomSampler::num_reads(settings.fastq_files, settings.target_num_reads);

            FastqWriter fastq_writer(settings.output_file);
            fastq_writer.write(fastq_entries);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::exit(-1);
    }

    return 0;
}
