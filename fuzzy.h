#ifndef FUZZY_H
#define FUZZY_H

#include <iostream>
#include <tuple>
#include <cmath>
#include <set>

using real_t = double;

class TriFuzzyNum {
    real_t l, m, u;

    constexpr std::tuple<real_t, real_t, real_t> rank() const {
        auto z = (u - l) + std::sqrt(1 + (u - m) * (u - m)) +
                 std::sqrt(1 + (m - l) * (m - l));
        auto x = ((u - l) * m + std::sqrt(1 + (u - m) * (u - m))
                    * l + std::sqrt(1 + (m - l) * (m - l)) * u) / z;
        auto y = (u - l) / z;
        return {x - y / 2, 1 - y, m};
    }

    constexpr void normalize() {
        if (m < l)
            std::swap(l, m);
        if (u < l)
            std::swap(l, u);
        if (u < m)
            std::swap(m, u);
    }

public:
    constexpr TriFuzzyNum(real_t l, real_t m, real_t u) : l{l}, m{m}, u{u} {
        normalize();
    }

    constexpr TriFuzzyNum(const TriFuzzyNum &) = default;

    constexpr TriFuzzyNum(TriFuzzyNum &&) = default;

    constexpr TriFuzzyNum& operator=(const TriFuzzyNum &) = default;

    constexpr TriFuzzyNum& operator=(TriFuzzyNum &&) = default;

    constexpr real_t lower_value() const { return l; }

    constexpr real_t modal_value() const { return m; }

    constexpr real_t upper_value() const { return u; }

    constexpr auto operator<=>(const TriFuzzyNum &o) const {
        return rank() <=> o.rank();
    };

    constexpr bool operator==(const TriFuzzyNum &o) const {
        return std::tuple(l, m, u) == std::tuple(o.l, o.m, o.u);
    };

    constexpr bool operator!=(const TriFuzzyNum &o) const {
        return !(*this == o);
    };

    constexpr TriFuzzyNum& operator+=(const TriFuzzyNum &o) {
        l += o.l;
        m += o.m;
        u += o.u;
        return *this;
    }

    constexpr TriFuzzyNum& operator-=(const TriFuzzyNum &o) {
        l -= o.u;
        m -= o.m;
        u -= o.l;
        return *this;
    }

    constexpr TriFuzzyNum& operator*=(const TriFuzzyNum &o) {
        l *= o.l;
        m *= o.m;
        u *= o.u;
        normalize();
        return *this;
    }

    constexpr TriFuzzyNum operator+(const TriFuzzyNum &o) const {
        TriFuzzyNum out(*this);
        out += o;
        return out;
    }

    constexpr TriFuzzyNum operator-(const TriFuzzyNum &o) const {
        TriFuzzyNum out(*this);
        out -= o;
        return out;
    }

    constexpr TriFuzzyNum operator*(const TriFuzzyNum &o) const {
        TriFuzzyNum out(*this);
        out *= o;
        return out;
    }

    friend std::ostream& operator<<(std::ostream &out, const TriFuzzyNum &tfm) {
        return out << "(" << tfm.l << ", " << tfm.m << ", " << tfm.u << ")";
    }
};

class TriFuzzyNumSet {
    std::multiset<TriFuzzyNum> set;
public:
    TriFuzzyNumSet(std::initializer_list<TriFuzzyNum> args);

    TriFuzzyNumSet();

    TriFuzzyNumSet(const TriFuzzyNumSet &);

    TriFuzzyNumSet(TriFuzzyNumSet &&);

    TriFuzzyNumSet& operator=(const TriFuzzyNumSet &);
    
    TriFuzzyNumSet& operator=(TriFuzzyNumSet &&);

    TriFuzzyNum arithmetic_mean() const;

    void insert(const TriFuzzyNum &t);

    void insert(TriFuzzyNum &&t);

    void remove(const TriFuzzyNum &t);
};

constexpr TriFuzzyNum crisp_number(real_t v) {
    return {v, v, v};
}

constinit inline TriFuzzyNum crisp_zero = crisp_number(0);

#endif
