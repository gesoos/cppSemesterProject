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

void VCFRow::setChrom(const std::string &chrom) {
	if (chrom.empty()) {
		exit(EXIT_FAILURE);
	}

	VCFRow::chrom = chrom;

	if (!this->check_chrom()) {
		exit(EXIT_FAILURE);
	}
}

int VCFRow::getPos() const {
	return pos;
}

void VCFRow::setPos(int pos) {
	if (pos < 0) {
		exit(EXIT_FAILURE);
	}

	VCFRow::pos = pos;
}

const std::string &VCFRow::getId() const {
	return id;
}

void VCFRow::setId(const std::string &id) {
	VCFRow::id = id;


	if (!this->check_id()) {
		exit(EXIT_FAILURE);
	}
}

const std::string &VCFRow::getRef() const {
	return ref;
}

void VCFRow::setRef(const std::string &ref) {
	VCFRow::ref = ref;

	if (!this->check_ref()) {
		exit(EXIT_FAILURE);
	}
}

const std::string &VCFRow::getAlt() const {
	return alt;
}

void VCFRow::setAlt(const std::string &alt) {
	VCFRow::alt = alt;

	if (!this->check_alt()) {
		exit(EXIT_FAILURE);
	}
}

float VCFRow::getQual() const {
	return qual;
}

void VCFRow::setQual(float qual) {
	VCFRow::qual = qual;
}

const std::string &VCFRow::getFilter() const {
	return filter;
}

void VCFRow::setFilter(const std::string &filter) {
	VCFRow::filter = filter;
}

const std::string &VCFRow::getInfo() const {
	return info;
}

void VCFRow::setInfo(const std::string &info) {
	VCFRow::info = info;
}

const std::string &VCFRow::getFormat() const {
	return format;
}

void VCFRow::setFormat(const std::string &format) {
	VCFRow::format = format;
}

const std::vector<std::string> &VCFRow::getSamples() const {
	return samples;
}

void VCFRow::setSamples(const std::vector<std::string> &samples) {
	VCFRow::samples = samples;
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
