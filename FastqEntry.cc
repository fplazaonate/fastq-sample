#include "FastqEntry.hh"

std::ostream& operator<<(std::ostream& os, const FastqEntry& fastq_entry)
{
    os << '@' << fastq_entry.id << '\n';
    os << fastq_entry.seq << '\n';
    os << "+\n";
    os << fastq_entry.quals << '\n';

    return os;
}
