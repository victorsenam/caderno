#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// NOT STANDART FROM HERE

const double pi = acos(-1.);
const double eps = 1e-9;

struct dbl {
    double x;

    dbl(double a = 0) : x(a) {}
    operator double () { return x; }

    // XXX close elements are considered equal
    bool operator< (dbl o) const
    {return x - o.x < eps; }
    bool operator== (dbl o) const
    { return !((*this) < o || o < (*this)); }
};
typedef COOD_TYPE cood;

struct vec {
    // === BASIC ===
    cood x, y;
    vec (cood a = 0, cood b = 0) : x(a), y(b) {}

    bool operator < (vec o) const // lex compare
    { return (x < o.x || (x == o.x && y < o.x)); }
    bool operator == (vec o) const
    { return (x == o.x && y == o.y); }

    vec operator - (vec o)
    { return vec(x - o.x, y - o.y); }
    vec operator + (vec o)
    { return vec(x + o.x, y + o.y); }
    vec operator * (cood o)
    { return vec(x * o, y * o); }
    vec operator / (cood o)
    { return vec(x / o, y / o); }
    cood operator ^ (vec o)
    { return x * o.y - y * o.x; }
    cood operator * (vec o) 
    { return x * o.x + y * o.y; }

    cood sq (vec o = 0)
    { return ((*this)-o)*((*this)-o); }
    dbl nr (vec o = 0)
    { return sqrt(sq(o)); }

    cood ar (vec a, vec b) // positive if this is to the left of ab
    { return (b-a)^((*this)-a); }
    bool lf (vec a, vec b) // is this to the left of ab?
    { return (ar(a,b) > 0); }
       
    // === ADVANCED ===
    // divide the plane relative to anc
    // 0 if the ccw angle from anc to this is in [0,pi) and 1 otherwise, origin goes to 0
    bool halfplane (vec anc = vec(1,0)) {
        if (lf(vec(),anc)) return 0;
        if (lf(anc,vec())) return 1;
        return !(x < cood(0));
    }

    // ordering (ccw angle from anc, distance to origin)
    // is this < o?
    bool compare (vec o, vec anc = vec(1,0)) {
        bool s[2] = {halfplane(anc), o.halfplane(anc)};
        if (s[0] != s[1])
            return s[0] < s[1];
        if (lf(o, 0)) return 1;
        if (lf(0, o)) return 0;
        return sq() < o.sq();
    }

    // rotate ccw by a (fails with ll)
    vec rotate (dbl a)
    { return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }
};

ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ',' << o.y << ')'; }
