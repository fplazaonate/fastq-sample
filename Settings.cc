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
#include <fstream>
#include <stdexcept>

Settings Settings::get_settings(int argc, char* argv[])
{
    Settings settings;

    // Create options decription
    po::options_description opts_desc( "Random sampling of reads from FASTQ files");

    opts_desc.add_options()
/bin/bash: qa : commande introuvable
        ("output-file,o", po::value<std::string>(&settings.output_file), "output FASTQ file")
        ("target-num-reads,r", po::value<size_t>(&settings.target_num_reads)->default_value(0), "number of reads to sample")
        ("target-num-bases,b", po::value<size_t>(&settings.target_num_bases)->default_value(0), "number of bases to sample")
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

    check_is_set("--fastq-files", settings.fastq_files);
    check_is_set("--output-file", settings.output_file);

    // Check input files
    for (std::vector<std::string>::const_iterator fastq_file = settings.fastq_files.begin(); fastq_file < settings.fastq_files.end(); ++fastq_file)
    {
        check_file_is_readable(*fastq_file);
    }

    // Check output file
    check_file_is_writable(settings.output_file);

    return (settings);
}

void Settings::check_file_is_readable(const std::string& filepath)
{
    std::ifstream ifs;
    ifs.open(filepath.c_str());

    if (ifs.good())
    {
        ifs.close();
    }
    else
    {
        std::ostringstream error_msg;
        error_msg  << "error: " << filepath << " cannot be read. Check that the path is valid and that you have read permissions.";
        throw (std::invalid_argument(error_msg.str()));
    }
}

void Settings::check_file_is_writable(const std::string& filepath)
{
    std::ofstream ofs;
    ofs.open(filepath.c_str(),  std::ios_base::in | std::ios_base::app);

    if (ofs.good())
    {
        ofs.close();
    }
    else
    {
        std::ostringstream error_msg;
        error_msg  << "error: " << filepath << " cannot be created. Check that the path is valid and that you have write permissions.";
        throw (std::invalid_argument(error_msg.str()));
    }
}

    template <typename T>
void Settings::check_is_set(const std::string& setting_name, const T& setting_value)
{
    if (setting_value.empty())
    {
        std::ostringstream error_msg;
        error_msg  << "error: " << setting_name << " required but missing.";
        throw (std::invalid_argument(error_msg.str()));
    }
}

