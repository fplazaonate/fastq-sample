#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <vector>
#include <string>

struct Settings
{
	std::vector<std::string> fastq_files;
	std::string output_file;
	size_t target_num_bases;
	size_t target_num_reads;
};

Settings get_settings(int argc, char* argv[]);
#endif // SETTINGS_HH
