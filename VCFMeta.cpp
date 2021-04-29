//
// Created by neitzerg on 4/24/2021.
//

#include "VCFMeta.h"
#include <sstream>

std::ostream &operator<<(std::ostream &out, const VCFMeta& meta) {
	bool printing_started = false;
	for (auto&& info : meta.metainfo) {
		if (!printing_started) {
			out << info;
			printing_started = true;
		}
		out << std::endl;
		out << info;
	}
	out << std::endl;
	return out;
}

std::string to_string(const VCFMeta& meta) {
	std::ostringstream ss;
	ss << meta;
	return ss.str();
}