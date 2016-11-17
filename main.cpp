#include <bits/stdc++.h>

using namespace std;

enum Types { INT = 0, FLOAT = 1, STRING = 2, LIST = 3 };
int ALLOW_ADD[] = {1, 1, 2, 3};
int ALLOW_MUL[] = {2, 1, 0, 0};

struct __attribute__((__packed__)) _int {
    Types type = INT;
    long long val;
};

struct __attribute__((__packed__)) _float {
    Types type = FLOAT;
    long double val;
};

struct __attribute__((__packed__)) _string {
    Types type = STRING;
    string val;
};

struct __attribute__((__packed__)) univ {
    void *ptr;

    void operator=(const univ &v) {
        switch (*(Types *)v.ptr) {
            case INT:
            case FLOAT:
                ptr = (_int *)v.ptr;
                break;
        }
    }

    void operator=(const int &val) { (*this) = (long long)val; }
    void operator=(const long &val) { (*this) = (long long)val; }
    void operator=(const long long &val) {
        ptr = new _int;
        ((_int *)ptr)->type = INT;
        ((_int *)ptr)->val = val;
    }

    void operator=(const float &val) { (*this) = (long double)val; }
    void operator=(const double &val) { (*this) = (long double)val; }
    void operator=(const long double &val) {
        ptr = new _float;
        ((_float *)ptr)->type = FLOAT;
        ((_float *)ptr)->val = val;
    }

    template <typename T>
    univ(T a) {
        (*this) = a;
    }
};

univ operator+(univ a, univ b) {
    assert(*(Types *)a.ptr == *(Types *)b.ptr);
    switch (*(Types *)a.ptr) {
        case INT:
            switch (*(Types *)b.ptr) {
                case INT: {
                    univ ans = ((_int *)a.ptr)->val + ((_int *)b.ptr)->val;
                    return ans;
                }
                case FLOAT: {
                    univ ans = ((_int *)a.ptr)->val + ((_float *)b.ptr)->val;
                    return ans;
                }
                default:
                    printf("Incompatible types for op '+' INT and STRING/LIST\n");
                    exit(1);
            }
        case FLOAT:
            switch (*(Types *)b.ptr) {
                case INT: {
                    univ ans = ((_float *)a.ptr)->val + ((_int *)b.ptr)->val;
                    return ans;
                }
                case FLOAT: {
                    univ ans = ((_float *)a.ptr)->val + ((_float *)b.ptr)->val;
                    return ans;
                }
                default:
                    printf("Incompatible types for op '+' FLOAT and STRING/LIST\n");
                    exit(1);
            }
    }
}

ostream &operator<<(ostream &os, univ a) {
    switch (*(Types *)a.ptr) {
        case INT:
            return os << ((_int *)a.ptr)->val;
        case FLOAT:
            return os << ((_float *)a.ptr)->val;
    }
}

int main() {
    cout << fixed << setprecision(6);
    univ s = 32.03;
    univ p = 0.0003;

    int i = 100000000;
    while (i--) {
        s = s + p;
    }
    cout << s << endl;
}
