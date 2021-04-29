//
// Created by neitzerg on 4/24/2021.
//

#ifndef PROJECT_VCFMETA_H
#define PROJECT_VCFMETA_H

#include <utility>
#include <vector>
#include <string>

class VCFMeta {
    std::vector<std::string> metainfo;

public:
    explicit VCFMeta(std::vector<std::string> info) : metainfo(std::move(info)) {}

    VCFMeta() = default;
    VCFMeta(const VCFMeta &vcf_meta) : metainfo(vcf_meta.metainfo) {}
    VCFMeta(VCFMeta &&vcf_meta)  noexcept : metainfo(vcf_meta.metainfo) {}
    ~VCFMeta() = default;
    VCFMeta &operator=(const VCFMeta &vcf_meta) {
        metainfo = vcf_meta.metainfo;
        return *this;
    }
    VCFMeta &operator=(VCFMeta &&vcf_meta)  noexcept {
        metainfo = vcf_meta.metainfo;
        return *this;
    }

	friend std::ostream& operator<<(std::ostream &out, const VCFMeta& meta);
};

std::ostream& operator<<(std::ostream &out, const VCFMeta& meta);

#endif //PROJECT_VCFMETA_H
