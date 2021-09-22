//
// Created by neitzerg on 4/24/2021.
//

#ifndef PROJECT_VCFROW_H
#define PROJECT_VCFROW_H

#include <string>
#include <vector>
#include <algorithm>


class VCFRow {
    std::string chrom;
    int pos;
    std::string id;
    std::string ref;
    std::string alt;
    float qual;
    std::string filter;
    std::string info;
    std::string format;
    std::vector<std::string> samples;

    size_t variant_count = 0;

	bool check_chrom();
	bool check_id();
	bool check_ref();
	bool check_alt();

public:
	const std::vector<std::string> BASE_CODES = {"A", "C", "G", "T", "N"};
    explicit VCFRow(std::vector<std::string> row_vals) {
        chrom = row_vals[0];
        pos = std::stoi(row_vals[1]);
        id = row_vals[2];
        ref = row_vals[3];
        alt = row_vals[4];

		if (alt.find(',') != std::string::npos) {
			variant_count += std::count(alt.begin(), alt.end(), ',');
		}
		variant_count++;

        qual = std::stof(row_vals[5]);
        filter = row_vals[6];
        info = row_vals[7];
        if (row_vals.size() > 8) {
            format = row_vals[8];
            for (int index = 9; index < row_vals.size(); index++) {
                samples.push_back(row_vals[index]);
            }
        }
    }

    VCFRow() = default;
    VCFRow(const VCFRow &vcf_row)
        : chrom(vcf_row.chrom)
        , pos(vcf_row.pos)
        , id(vcf_row.id)
        , ref(vcf_row.ref)
        , alt(vcf_row.alt)
        , qual(vcf_row.qual)
        , filter(vcf_row.filter)
        , info(vcf_row.info)
        , format(vcf_row.format)
        , samples(vcf_row.samples)
        , variant_count(vcf_row.variant_count)
    { }
    VCFRow(VCFRow &&vcf_row)
            : chrom(vcf_row.chrom)
            , pos(vcf_row.pos)
            , id(vcf_row.id)
            , ref(vcf_row.ref)
            , alt(vcf_row.alt)
            , qual(vcf_row.qual)
            , filter(vcf_row.filter)
            , info(vcf_row.info)
            , format(vcf_row.format)
            , samples(vcf_row.samples)
            , variant_count(vcf_row.variant_count)
    { }
    ~VCFRow() = default;
    VCFRow &operator=(const VCFRow &vcf_row) {
        chrom = vcf_row.chrom;
        pos = vcf_row.pos;
        id = vcf_row.id;
        ref = vcf_row.ref;
        alt = vcf_row.alt;
        qual = vcf_row.qual;
        filter = vcf_row.filter;
        info = vcf_row.info;
        format = vcf_row.format;
        samples = vcf_row.samples;
        variant_count = vcf_row.variant_count;
        return *this;
    }
    VCFRow &operator=(VCFRow &&vcf_row) {
        chrom = vcf_row.chrom;
        pos = vcf_row.pos;
        id = vcf_row.id;
        ref = vcf_row.ref;
        alt = vcf_row.alt;
        qual = vcf_row.qual;
        filter = vcf_row.filter;
        info = vcf_row.info;
        format = vcf_row.format;
        samples = vcf_row.samples;
        variant_count = vcf_row.variant_count;
        return *this;
    }

    std::string get_chrom();

    size_t get_variant_count();

	bool is_valid();

    friend std::ostream& operator<<(std::ostream &out, const VCFRow& row);


};

std::ostream& operator<<(std::ostream &out, const VCFRow& row);
#endif //PROJECT_VCFROW_H
