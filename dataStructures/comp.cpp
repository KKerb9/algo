#include "tmp.cpp"

template<typename T>
struct Comp {
        bool operator() (const T& a, const T& b) const {
                return a < b;
        }
};