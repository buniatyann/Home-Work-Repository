#include <list>
#include <vector>
#include <utility>
#include <iostream>

template <typename DegreeType, typename CoeffType>
std::list<std::pair<DegreeType, CoeffType>> PolynomSorter(const std::vector<std::pair<DegreeType, CoeffType>>& input) {
    std::list<std::pair<DegreeType, CoeffType>> lst;

    for (const auto& pair : input) {
        DegreeType degree = pair.first;
        CoeffType value = pair.second;

        if (lst.empty()) {
            lst.emplace_back(degree, value);
        } 
        else {
            bool inserted = false;
            if (lst.front().first < degree) {
                lst.emplace_front(degree, value);
                inserted = true;
            }
            else if (lst.back().first > degree) {
                lst.emplace_back(degree, value);
                inserted = true;
            }

            if (!inserted) {
                for (auto it = lst.begin(); it != lst.end(); ++it) {
                    if (it->first == degree) {
                        it->second += value;
                        inserted = true;
                        break;
                    }
                    if (it->first < degree) {
                        lst.insert(it, {degree, value});
                        inserted = true;
                        break;
                    }
                }
            }
        }
    }

    return lst;
}
