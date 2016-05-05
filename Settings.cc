/*
 * Copyright 2016 Enterome
 *
 * This file is part of fastq-sample
 *
 * fastq-sample is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * fastq-sample is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fastq-sample. If not, see <http://www.gnu.org/licenses/>.
 */

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
