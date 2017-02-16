#ifndef C_geometry_misc
#define C_geometry_misc

#include "header.cpp"

// Does the interval [a.first,a.second] intersect with [b.first,b.second]?
// -1 : no intersection
// 0 : intersects on the border
// 1 : intersects properly
tmpl inline int intersects (pair<cood,cood> a, pair<cood,cood> b)
{ return -1 + (lte(a.first,b.second) && lte(b.first,a.second)) + (lt(a.first,b.second) && lt(b.first,a.second)); }

// Does the interval [a.first,a.second] contain [b.first,b.second]?
// -1 : no
// 0 : borders coincede (at least one)
// 1 : contains properly
tmpl inline int contains (pair<cood,cood> a, pair<cood,cood> b)
{ return -1 + (lte(a.first,b.first) && lte(b.second,a.second)) + (lt(a.first,b.first) && lt(b.second,a.second)); }

#endif
