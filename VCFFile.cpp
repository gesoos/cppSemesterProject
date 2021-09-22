//
// Created by neitzerg on 4/24/2021.
//

#include "VCFFile.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

std::vector<VCFRow> VCFFile::get_variants(const std::string& chrom) {
    std::vector<VCFRow> filtered_rows;
    std::copy_if(rows.begin(), rows.end(),
                 std::back_inserter(filtered_rows),
                 [chrom](VCFRow& row) { return row.get_chrom() == chrom; });
    return filtered_rows;
}

size_t VCFFile::get_total_variant_count() const {
    return total_variant_count;
}

size_t VCFFile::get_sample_count() const {
    return header.get_sample_count();
}

void VCFFile::parse_header(std::string header_line) {
    header_line.erase(0, 1);
    size_t pos;
    std::string delimiter = "\t";
    std::string token;
    std::vector<std::string> header_cols;
    while ((pos = header_line.find(delimiter)) != std::string::npos) {
        token = header_line.substr(0, pos);
        header_cols.push_back(token);
        header_line.erase(0, pos + delimiter.length());
    }
	if (!header_line.empty()) {
		header_cols.push_back(header_line);
	}
    header = VCFHeader(header_cols);
}

VCFRow VCFFile::parse_row(std::string row) {
    size_t pos;
    std::string delimiter = "\t";
    std::string token;
    std::vector<std::string> row_vals;
    while ((pos = row.find(delimiter)) != std::string::npos) {
        token = row.substr(0, pos);
        row_vals.push_back(token);
        row.erase(0, pos + delimiter.length());
    }
    if (!row.empty()) {
    	row_vals.push_back(row);
    }
    VCFRow vcf_row = VCFRow(row_vals);

    if (!vcf_row.is_valid()) {
    	exit(EXIT_FAILURE);
    }

    total_variant_count += vcf_row.get_variant_count();
    return vcf_row;
}

std::vector<VCFRow> VCFFile::get_parsed_rows(const std::vector<std::string>& row_lines) {
    std::vector<VCFRow> parsed_rows;
    parsed_rows.reserve(row_lines.size());
    for (auto&& row_line : row_lines) {
        parsed_rows.push_back(parse_row(row_line));
    }
    return parsed_rows;
}

void VCFFile::set_rows(std::vector<VCFRow> parsed_rows) {
    this->rows = std::move(parsed_rows);
}

void VCFFile::read_VCF(const std::string& filename) {
    std::ifstream in(filename, std::ios::in);
    std::string line;
    std::vector<std::string> meta_lines;
    std::string header_line;
    std::vector<std::string> row_lines;
    while (std::getline(in, line)) {
        if (line.rfind(META_START, 0) == 0) {
            if (!header_line.empty()) {
            	std::cout << "Found meta information after header line.";
				exit (EXIT_FAILURE);
            }

            if (!row_lines.empty()) {
				std::cout << "Found meta information after variant lines started.";
				exit (EXIT_FAILURE);
            }

            meta_lines.push_back(line);
        } else if (line.rfind(HEADER_START, 0) == 0) {
            if (!header_line.empty()) {
				std::cout << "Found more than one header line.";
				exit (EXIT_FAILURE);
            }

            if (!row_lines.empty()) {
				std::cout << "Found header line after variant lines started.";
				exit (EXIT_FAILURE);
            }

            header_line = line;
        } else {
            if (header_line.empty()) {
				std::cout << "Found no header line.";
				exit (EXIT_FAILURE);
            }

            row_lines.push_back(line);
        }
    }
    in.close();
    metainfo = VCFMeta(meta_lines);
    parse_header(header_line);
    rows = get_parsed_rows(row_lines);
}

void VCFFile::write_VCF(const std::string &filename) {
	std::ofstream out(filename, std::ios::out);
	if (out.is_open()) {
		out << metainfo;
		out << header;
		for (auto &&row : rows) {
			out << row;
		}
	} else {
		std::cout << "Could not open file for writing.";
		exit (EXIT_FAILURE);
	}
	out.close();
}
