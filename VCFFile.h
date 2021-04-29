//
// Created by neitzerg on 4/24/2021.
//

#ifndef PROJECT_VCFFILE_H
#define PROJECT_VCFFILE_H


#include <vector>
#include "VCFRow.h"
#include "VCFHeader.h"
#include "VCFMeta.h"

class VCFFile {
    const std::string META_START = "##";
    const std::string HEADER_START = "#";
    VCFMeta metainfo;
    VCFHeader header;
    std::vector<VCFRow> rows;
    size_t total_variant_count = 0;

    void parse_header(std::string header_line);
    VCFRow parse_row(std::string row);
    void set_rows(std::vector<VCFRow> parsed_rows);
    std::vector<VCFRow> get_parsed_rows(const std::vector<std::string>& row_lines);

public:
    void read_VCF(const std::string& filename);
    void write_VCF(const std::string& filename);

    // getting all variants from one chromosome
    std::vector<VCFRow> get_variants(const std::string& chrom);
    // getting the overall variant count
    [[nodiscard]] size_t get_total_variant_count() const;
    // getting the number of samples in the file
    [[nodiscard]] size_t get_sample_count() const;
};


#endif //PROJECT_VCFFILE_H
