#include "FastqWriter.hh"

FastqWriter::FastqWriter(const std::string& fastq_file)
	: fastq_file_(fastq_file), ofs_(fastq_file_.c_str())
{
}

FastqWriter::~FastqWriter()
{
	ofs_.close();
}

void FastqWriter::write(const std::vector<FastqEntry>& fastq_entries)
{
	for (std::vector<FastqEntry>::const_iterator fastq_entry = fastq_entries.begin();
			fastq_entry != fastq_entries.end(); ++fastq_entry)
	{
		write(*fastq_entry);
	}
}

void FastqWriter::write(const std::vector<FastqEntry>& fastq_entries, const std::vector<size_t>& indexes)
{
	for (std::vector<size_t>::const_iterator index = indexes.begin();
			index != indexes.end(); ++index)
	{
		const FastqEntry& fastq_entry = fastq_entries[*index];
		write(fastq_entry);
	}
}

void FastqWriter::write(const FastqEntry& fastq_entry)
{
	ofs_ << '@' << fastq_entry.id << '\n';
	ofs_ << fastq_entry.seq << '\n';
	ofs_ << '+' << '\n';
	ofs_ << fastq_entry.quals << '\n';
}
