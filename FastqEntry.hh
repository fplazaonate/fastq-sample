#ifndef FASTQ_SEQUENCE_HH
#define FASTQ_SEQUENCE_HH

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
