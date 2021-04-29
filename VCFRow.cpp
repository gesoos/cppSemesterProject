//
// Created by neitzerg on 4/24/2021.
//

#include "VCFRow.h"
#include <sstream>

std::string VCFRow::get_chrom() {
	return chrom;
}

size_t VCFRow::get_variant_count() {
	return variant_count;
}

std::ostream &operator<<(std::ostream &out, const VCFRow& row) {
	out << row.chrom << "\t" << row.pos << "\t" << row.id << "\t" << row.ref << "\t" << row.alt
			<< "\t" << row.qual << "\t" << row.filter << "\t" << row.info;
	if (!row.format.empty()) {
		out << "\t" << row.format;
		if (!row.samples.empty()) {
			for (auto&& sample : row.samples) {
				out << "\t" << sample;
			}
		}
	}
	out << std::endl;
	return out;
}

std::string to_string(const VCFRow& row) {
	std::ostringstream ss;
	ss << row;
	return ss.str();
}
