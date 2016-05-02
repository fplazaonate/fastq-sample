#include "Settings.hh"
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <iostream>
#include <stdexcept>

Settings get_settings(int argc, char* argv[])
{
	Settings settings;

	// Create options decription
	po::options_description opts_desc( "");

	opts_desc.add_options()
		("help,h", "print this help message")
		("fastq-files,f", po::value<std::vector<std::string> >(&settings.fastq_files)->multitoken()/*->required()*/, "")
		("output-file,o", po::value<std::string>(&settings.output_file)/*->required()*/, "")
		("target-num-bases,b", po::value<size_t>(&settings.target_num_bases)->default_value(0), "")
		("target-num-reads,r", po::value<size_t>(&settings.target_num_reads)->default_value(0), "")
		;

	// Retrieve and parse command line settings
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, opts_desc), vm);

	// Print help
	if (argc == 1 || vm.count("help"))
	{
		std::cout << opts_desc << std::endl;
		std::exit(0);
	}

	po::notify(vm);

	// TODO Check fastq files

	return (settings);
}
