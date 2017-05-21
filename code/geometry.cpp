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

struct vec {
    // === BASIC ===
    cood x, y;
    vec () : x(0), y(0) {}
    vec (cood a, cood b) : x(a), y(b) {}
    friend ostream& operator<<(ostream& os, vec o);

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

    cood sq (vec o = vec())
    { return ((*this)-o)*((*this)-o); }
    double nr (vec o = vec())
    { return sqrt(sq(o)); }

    cood ar (vec a, vec b) // positive if this is to the left of ab
    { return (b-a)^((*this)-a); }
    bool lf (vec a, vec b) // is this to the left of ab?
    { return (ar(a,b)) > eps; }
       
    // === ADVANCED ===
    // divide the plane relative to anc
    // 0 if the ccw angle from anc to this is in [0,pi) and 1 otherwise, origin goes to 0
    bool halfplane (vec anc = vec(1,0)) {
        if (lf(vec(),anc)) return 0;
        if (lf(anc,vec())) return 1;
        return (x < -eps);
    }

    // ordering (ccw angle from anc, distance to origin)
    // is this < o?
    // PRECISION : ok with double if norm in [-1e4,1e3]
    bool compare (vec o, vec anc = vec(1,0)) {
        bool s[2] = {halfplane(anc), o.halfplane(anc)};
        if (s[0] != s[1])
            return s[0] < s[1];

        if (lf(o, vec())) return 1;
        if (lf(vec(), o)) return 0;
        return sq() < o.sq() - eps;
    }

    // rotate ccw by a (fails with ll)
    vec rotate (double a)
    { return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }
};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }
