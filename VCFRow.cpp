//
// Created by neitzerg on 4/24/2021.
//

#include "VCFRow.h"
#include <sstream>
#include <cctype>
#include <regex>

std::string VCFRow::get_chrom() {
	return chrom;
}

size_t VCFRow::get_variant_count() {
	return variant_count;
}

bool VCFRow::check_chrom() {
	for (auto &&letter : chrom) {
		if (isspace(letter)) {
			return false;
		}
	}
	return true;
}

bool VCFRow::check_id() {
	if (!id.empty()) {
		for (auto &&letter : id) {
			if (isspace(letter) || letter == ';') {
				return false;
			}
		}
	}
	return true;
}

bool VCFRow::check_ref() {
	for (auto &&base : ref) {
		if (std::find(BASE_CODES.begin(), BASE_CODES.end(), base) == BASE_CODES.end()) {
			return false;
		}
	}
	return true;
}

bool VCFRow::check_alt() {
	const std::regex alt_regex("([ACGTNacgtn]+|\\*|\\.)(,([ACGTNacgtn]+|\\*|\\.))*");
	if (!std::regex_match(alt, alt_regex)) {
		return false;
	}
	return true;
}

bool VCFRow::is_valid() {
	if (chrom.empty() || pos < 0) {
		return false;
	} else if (check_chrom() && check_id() && check_ref() && check_alt()) {
		return true;
	} else {
		return false;
	}
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
