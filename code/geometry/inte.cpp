#include "header.cpp"
#define ite inte<cood>

template<typename cood> struct inte {
    cood a,b;

    ite () {}
    ite (cood s, cood t) : a(s), b(t)
    { if (a > b) swap(a,b); }
    explicit ite (cood x) : a(x), b(x) {}

    // XXX assumes a <= b
    inline cood size () const
    { return b - a; }

    // XXX assumes a <= b
    inline bool contains (ite ot, cood eps = 0) const
    { return lte(a,ot.a,eps) && lte(ot.b,b,eps);}
    // XXX assumes a <= b
    inline bool intersects (ite ot, cood eps = 0) const
    { return contains(ite(ot.a), eps) || contains(ite(ot.b), eps) || ot.contains(*this, eps); }
};
