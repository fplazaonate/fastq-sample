#ifndef FASTQ_WRITER
#define FASTQ_WRITER

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
