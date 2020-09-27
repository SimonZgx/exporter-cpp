//
// Created by Administrator on 2020/9/27.
//

#ifndef EXPORTER_CPP_COLLECTOR_H
#define EXPORTER_CPP_COLLECTOR_H

#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <stdint.h>
#include <cassert>
#include <set>
#include <algorithm>


namespace exporter {

    using std::string;
    using std::vector;
    using std::set;
    using std::map;
    using Labels = map<string, string>;
    using LabelPair = std::pair<string, string>;

    const char reservedLabelPrefix[] = "__";

    bool isValidMetricName(string name) {
        if (name.empty()) return false;
        for (const char c : name) {
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') || (c == ':') ||
                  (c >= '0' && c <= '9'))) {
                return false;
            }
        }
        return true;
    }

    bool isValidLabelName(string name) {
        if (name.empty()) return false;
        for (const char c : name) {
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') ||
                  (c >= '0' && c <= '9'))) {
                return false;
            }
        }

        if (strncmp(name.substr(0, 2).c_str(), reservedLabelPrefix, 2) != 0) {
            return false;
        }
        return true;
    }

    namespace {
        struct Description {
            string name;
            string help;
            vector<LabelPair> constLabelPairs;
            vector<string> variableLabels;
            uint64_t id;
            uint64_t dimHash;
        };
    }

    Description *newDesc(const string &name, const string &help,
                         const vector<string> &variableLabels, const Labels &constLabels) {
        assert(isValidMetricName(name));
        auto *desc = new Description();
        desc->name = name;
        desc->variableLabels = variableLabels;
        desc->help = help;
        vector<string> labelValues, labelNames;
        set<string> labelNameSet;
        labelValues.emplace_back(name);
        for (const auto &it: constLabels) {
            assert(isValidLabelName(it.first));
            labelNames.emplace_back(it.first);
            labelNameSet.insert(it.first);
        }

        std::sort(labelNames.begin(), labelNames.end());
        for (const auto &it: labelNames) {
            labelValues.emplace_back(constLabels.find(it)->second);
        }
        assert(labelValues.size() == (constLabels.size() + 1));

        return desc;
    }

    class Collector {

    };
}


#endif //EXPORTER_CPP_COLLECTOR_H
