#include <iostream>
#include "VCFFile.h"

int main() {
    std::string filename = "D:\\UNI\\C++\\Project\\test.vcf";
    VCFFile vcf_file;
    vcf_file.read_VCF(filename);
	std::vector<VCFRow> variants_from_20 = vcf_file.get_variants("20");
	size_t variant_count_from_20 = 0;
	for (auto&& row : variants_from_20) {
		variant_count_from_20 += row.get_variant_count();
	}
    std::cout << "The file " << filename << " contains " << vcf_file.get_sample_count() << " samples," << std::endl;
    std::cout << vcf_file.get_total_variant_count() << " variants," << std::endl;
    std::cout << "and " << variants_from_20.size() <<  " variant lines from chromosome 20," << std::endl;
    std::cout << "representing " << variant_count_from_20 << " variants.";

    std::string out_file = "D:\\UNI\\C++\\Project\\test_out.vcf";
    vcf_file.write_VCF(out_file);
    return 0;
}
