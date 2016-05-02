#ifndef FASTQ_MULTI_READER_HH
#define FASTQ_MULTI_READER_HH

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
