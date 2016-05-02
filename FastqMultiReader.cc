#include "FastqMultiReader.hh"

FastqMultiReader::FastqMultiReader(const std::vector<std::string>& fastq_files)
    : fastq_files_(fastq_files), cur_fastq_file_(fastq_files_.begin()), cur_fastq_reader_(NULL)
{
    if (cur_fastq_file_ != fastq_files_.end())
    {
        cur_fastq_reader_ = std::auto_ptr<FastqReader>(new FastqReader(*cur_fastq_file_));
    }
}
bool FastqMultiReader::next_entry(FastqEntry& fastq_entry)
{
    while (cur_fastq_file_ != fastq_files_.end())
    {
        if (cur_fastq_reader_->next_entry(fastq_entry))
        {
            return true;
        }

        ++cur_fastq_file_;
        if (cur_fastq_file_ != fastq_files_.end())
        {
            cur_fastq_reader_ = std::auto_ptr<FastqReader>(new FastqReader(*cur_fastq_file_));
        }
    }

    return false;
}

bool FastqMultiReader::next_chunk(std::vector<FastqEntry>& fastq_entries, const size_t chunk_size)
{
    fastq_entries.clear();

    if (cur_fastq_file_ == fastq_files_.end())
        return false;

    FastqEntry fastq_entry;
    fastq_entries.reserve(chunk_size);
    while (fastq_entries.size() < chunk_size && next_entry(fastq_entry))
    {
        fastq_entries.push_back(fastq_entry);
    }

    return !fastq_entries.empty();
}

bool FastqMultiReader::all_entries(std::vector<FastqEntry>& fastq_entries)
{
    fastq_entries.clear();

    std::vector<FastqEntry> chunk;
    while (next_chunk(chunk))
    {
        fastq_entries.insert(fastq_entries.end(), chunk.begin(), chunk.end());
    }

    return true;
}
