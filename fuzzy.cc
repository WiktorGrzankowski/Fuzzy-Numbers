#include "fuzzy.h"

TriFuzzyNumSet::TriFuzzyNumSet(std::initializer_list<TriFuzzyNum> args):
    set{args} {}

TriFuzzyNumSet::TriFuzzyNumSet(): set{} {}

TriFuzzyNumSet::TriFuzzyNumSet(const TriFuzzyNumSet &) = default;

TriFuzzyNumSet::TriFuzzyNumSet(TriFuzzyNumSet &&) = default;

TriFuzzyNumSet& TriFuzzyNumSet::operator=(const TriFuzzyNumSet &) = default;

TriFuzzyNumSet& TriFuzzyNumSet::operator=(TriFuzzyNumSet &&) = default;

TriFuzzyNum TriFuzzyNumSet::arithmetic_mean() const {
    if (set.empty())
        throw std::length_error(
                "TriFuzzyNumSet::arithmetic_mean - the set is empty.");
    real_t l{0}, m{0}, u{0};
    for (const TriFuzzyNum& fuzzy: set) {
        l += fuzzy.lower_value();
        m += fuzzy.modal_value();
        u += fuzzy.upper_value();
    }
    l /= set.size();
    m /= set.size();
    u /= set.size();
    return {l, m, u};
}

void TriFuzzyNumSet::insert(const TriFuzzyNum &t) {
    set.insert(t);
}

void TriFuzzyNumSet::insert(TriFuzzyNum &&t) {
    set.insert(t);
}

void TriFuzzyNumSet::remove(const TriFuzzyNum &t) {
    set.erase(t);
}
