#include "../header.cpp"

const double pi = acos(-1.);

// ## about eps ##
// many functions recieve an optional parameter eps
// when dealing with floating point numbers, eps is the size of a point
// if you want points to be considered as existant, eps should be positive
// otherwise, eps should be negative

// ## position functions ##
// functions that refer to position (inside, contains, intersects, etc)
// and return an integer follow a standart
// examples are based the return of pl.inside(p) given a poly pl and a 
// vect p
// 1 : respects fully (eg: p is fully strictly inside pl)
// 0 : respects only for a point (eg: p is on the border of pl)
// -1 : does not respect (eg: p is outside of pl)
