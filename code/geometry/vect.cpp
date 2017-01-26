#include "header.cpp"
#define vec vect<cood>

template<typename cood> struct vect {
    cood x,y;
    
    // constructors
    vec () {}
    vec (cood a, cood b) : x(a), y(b) {}

    // basics
    inline bool operator < (vec ot) const // lex compare
    { return (x < ot.x || (x == ot.x && y < ot.y)); }

    // transforming
    inline vec operator - (vec ot) const
    { return vec(x - ot.x, y - ot.y); }
    inline vec operator + (vec ot) const
    { return vec(x + ot.x, y + ot.y); }
    inline vec operator * (cood a) const
    { return vec(x * a, y * a); }
    inline vec operator / (cood a) const
    { return vec(x / a, y / a); }
    inline vect<double> rotate (double ang) const // counter-clockwise
    { return vect<double>(cos(ang) * x - sin(ang) * y, sin(ang) * x + cos(ang) * y); }

    // math
    inline cood operator ^ (vec ot) const // cross
    { return x * ot.y - y * ot.x; }
    inline cood operator * (vec ot) const // inner
    { return x * ot.x + y * ot.y; }
    inline cood sq (vec ot = vec(0,0)) const // squared 2-norm (and distance)
    { return ((*this)-ot)*((*this)-ot); }
    inline double nr (vec ot = vec(0,0)) const // 2-norm (and distance)
    { return sqrt(sq(ot)); }
    inline cood ar (vec a, vec b) const // oriented area (positive if b is to the left of a)
    { return (a-(*this))^(b-(*this)); }

    // XXX: not a full comparsion operator, use compare for ordering
    // counter-clockwise comparsion (to the left means greater)
    // returns -1 if a < b [a->b is counter-clockwise]
    // returns 0 if a == b [colinear]
    // returns 1 if a > b [a->b is clockwise]
    int left (vec a, vec b, cood eps = 0) const
    { cood o = ar(a, b); return (o < -eps) - (o > eps); }

    // divide the plane by anc
    // returns 0 if the counter-clockwise angle between anc and this is x s.t. 0 <= x < pi
    // returns 1 otherwise (pi <= x < 2pi)
    inline bool halfplane (vec anc = vec(1,0), cood eps = 0) const {
        int o = vec(0,0).left(anc, *this, eps);
        if (o == 0)
            return (*this)*(anc) < 0;
        return (o == 1);
    }

    // full comparsion
    // orders by clockwise order starting from the (0,-1) direction (upwards)
    // settles draws by proximity to this point
    bool compare (vec ot, vec anc = vect<cood>(1,0), cood eps = 0) const {
        bool s[2] = {halfplane(anc, eps), ot.halfplane(anc, eps)};
        if (s[0] != s[1])
            return s[0] < s[1];

        int pr = vec(0,0).left((*this), ot, eps);
        if (pr)
            return (pr < 0);
        return sq() < ot.sq();
    }
};
