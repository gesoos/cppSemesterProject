//
// Created by neitzerg on 4/24/2021.
//

#ifndef PROJECT_VCFHEADER_H
#define PROJECT_VCFHEADER_H


#include <utility>
#include <vector>
#include <string>

class VCFHeader {
    const size_t MANDATORY_COLUMNS_COUNT = 8;
    const size_t NOT_SAMPLE_COLUMN_COUNT = 9;
    std::vector<std::string> column_names;

public:
    explicit VCFHeader(std::vector<std::string>  col_names) : column_names(std::move(col_names)) {}

    VCFHeader() = default;
    VCFHeader(const VCFHeader &vcf_header) : column_names(vcf_header.column_names) {}
    VCFHeader(VCFHeader &&vcf_header)  noexcept : column_names(vcf_header.column_names) {}
    ~VCFHeader() = default;
    VCFHeader &operator=(const VCFHeader &vcf_header) {
        column_names = vcf_header.column_names;
        return *this;
    }
    VCFHeader &operator=(VCFHeader &&vcf_header)  noexcept {
        column_names = vcf_header.column_names;
        return *this;
    }

	friend std::ostream& operator<<(std::ostream &out, const VCFHeader& header);

    [[nodiscard]] size_t get_column_count() const;
    [[nodiscard]] size_t get_sample_count() const;
};

std::ostream& operator<<(std::ostream &out, const VCFHeader& header);

#endif //PROJECT_VCFHEADER_H
