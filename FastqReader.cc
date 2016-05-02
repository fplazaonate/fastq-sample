#include "FastqReader.hh"

FastqReader::FastqReader(const std::string& filepath)
    : filepath_(filepath), filestream_(filepath_.c_str(), std::ios_base::in), line_()
{
    line_.reserve(10000);
}

FastqReader::~FastqReader()
{
    filestream_.close();
}

bool FastqReader::next_entry(FastqEntry& fastq_entry)
{
    if (!filestream_.good())
    {
        return false;
    }

    // Step 1: read entry header
    std::getline(filestream_, line_);
    if (line_.empty())
    {
        // Sometimes FASTQ files have empty last line_s
        filestream_.setstate(std::ios::eofbit);  
        return false;
    }

    if (line_[0] != '@')
    {
        // TODO: had error msg
        filestream_.setstate(std::ios::failbit);  
        return false;
    }
    fastq_entry.id = line_.substr(1);

    // Step 2: read entry sequence
    std::getline(filestream_, fastq_entry.seq);
    if (fastq_entry.seq.empty()) 
    {
        // TODO: had error msg
        filestream_.setstate(std::ios::failbit);  
        return false;
    }

    // Step 3: read quals separator
    std::getline(filestream_, line_);
    if (line_.empty() || line_[0] != '+') 
    {
        // TODO: had error msg
        filestream_.setstate(std::ios::failbit);  
        return false;
    }

    // Step 4: read quals
    std::getline(filestream_, fastq_entry.quals);
    if (fastq_entry.quals.empty()) 
    {
        // TODO: had error msg
        filestream_.setstate(std::ios::failbit);  
        return false;
    }
    return true;
}
