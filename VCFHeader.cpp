//
// Created by neitzerg on 4/24/2021.
//

#include "VCFHeader.h"
#include <sstream>

size_t VCFHeader::get_sample_count() const {
    if (column_names.size() > MANDATORY_COLUMNS_COUNT) {
        return column_names.size() - NOT_SAMPLE_COLUMN_COUNT;
    }
    return 0;
}

size_t VCFHeader::get_column_count() const {
    return column_names.size();
}

std::ostream &operator<<(std::ostream &out, const VCFHeader& header) {
	bool printing_started = false;
	for (auto&& column : header.column_names) {
		if (!printing_started) {
			out << column;
			printing_started = true;
		}
		out << "\t" << column;
	}
	out << std::endl;
	return out;
}

std::string to_string(const VCFHeader& header) {
	std::ostringstream ss;
	ss << header;
	return ss.str();
}
