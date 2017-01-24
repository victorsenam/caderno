#include "header.cpp"

template<typename cood> struct interval {
    cood a,b;

    interval<cood> () {}
    interval<cood> (cood s, cood t) : a(s), b(t)
    { if (a > b) swap(a,b); }
    interval<cood> (cood x) : a(x), b(x) {}

    // XXX assumes a <= b
    inline cood size () const
    { return b - a; }

    // XXX assumes a <= b
    inline bool contains (const interval & ot, cood eps = 0) const
    { return lte(a,ot.a,eps) && lte(ot.b,b,eps);}
    // XXX assumes a <= b
    inline bool intersects (const interval & ot, cood eps = 0) const
    { return contains(interval<cood>(ot.a), eps) || contains(interval<cood>(ot.b), eps) || ot.contains(*this, eps); }
};
