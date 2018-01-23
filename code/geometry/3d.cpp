struct pnt { // TODO it's not tested at all :)
	cood x, y, z;
	pnt () : x(0), y(0), z(0) pnt (cood a, cood b, cood c) : x(a), y(b), z(c) {}
	inline pnt operator - (pnt o) { return pnt(x - o.x, y - o.x, z - o.z); }
	inline pnt operator + (pnt o) { return pnt(x + o.x, y + o.x, z + o.z); }
	inline pnt operator * (cood o) { return pnt(x*o, y*o, z*o); }
	inline pnt operator / (cood o) { return pnt(x/o, y/o, z/o); }
	inline cood operator * (pnt o) { return x*o.x + y*o.y + z*o.z; } // inner: |this||o|*cos(ang)
	inline pnt operator ^ (pnt o) { return pnt(y*o.z - o.y*z, z*o.x - o.z*x, x*o.y - o.x*y); } // cross: oriented normal to the plane containing the two vectors, has norm |this||o|*sin(ang)
	inline cood operator () (pnt a, pnt b) { return (*this)*(a^b); } // mixed: positive on the right-hand rule (thumb=this,index=a,mid=b)

	inline cood inner (pnt a, pnt b) { return (a-(*this))*(b-(*this)); }
	inline vec cross (pnt a, pnt b) { return (a-(*this))^(b-(*this)); } // its norm is twice area of triangle
	inline cood mixed (pnt a, pnt b, pnt c) { return (a-(*this))(b-(*this),c-(*this)); } // 6 times the oriented area of thetahedra

	inline cood sq (pnt o = vec()) { return inner(o,o); }
	inline double nr (pnt o = vec()) { return sqrt(sq(o)); }

	inline bool in_seg (pnt a, pnt b) { return cross(a,b).sq() <= eps && inner(a,b) <= eps; } // tips included
	inline bool in_tri (pnt a, pnt b, pnt c) { return abs(mixed(a,b,c)) <= eps && cross(a,b)*cross(b,c) >= -eps && cross(a,b)*cross(c,a) >= -eps; } // border included

	inline pnt proj (pnt a, pnt b) { return a + (b-a)*((b-a)*(*this))/(sq()); } // onto line ab
	inline pnt proj (pnt a, pnt b, pnt c) { return (*this) - ((b-a)^(c-a)).proj((*this)-a); } // onto plane abc

	inline double dist2_lin (pnt a, pnt b) { return ((a-(*this))^(b-(*this))).sq() / ((b-a).sq()*4); }
	inline double dist2_seg (pnt a, pnt b) { pnt p = proj(a,b); return p.in_seg(a,b) ? dist2_lin(a,b) : min(p.sq(a),p.sq(b)); }
	inline double dist2_pln (pnt a, pnt b, pnt c) { return sq(proj(a,b,c)); }
	inline double dist2_tri (pnt a, pnt b, pnt c) { pnt p = proj(a,b,c); return p.in_tri(a,b,c) ? sq(p) : min({ dist2_seg(a,b), dist2_seg(b,c), dist2_seg(c,a) }); }
};
inline cood area (pnt a, pnt b, pnt c) { abs(a.cross(b,c).nr())/2; }
inline cood vol (pnt a, pnt b, pnt c, pnt d) { abs((b-a).mixed(c-a,d-a)) / 6; } // thetahedra

// area de calota na altura h : 2.pi.R.h
// volume de calota na altura h : pi.h/6 * (3r^2 + h^2)

