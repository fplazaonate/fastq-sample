#ifndef FASTQ_READER_HH
#define FASTQ_READER_HH

#include <string>
#include <fstream>
#include "FastqEntry.hh"

class FastqReader
{
    public:
        FastqReader(const std::string& filepath);
        ~FastqReader();
        bool next_entry(FastqEntry& fastq_entry);

    private:
        const std::string filepath_;
        std::ifstream filestream_;
        std::string line_;
};

#endif // FASTQ_READER_HH
