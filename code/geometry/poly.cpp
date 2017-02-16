#ifndef C_geometry_poly
#define C_geometry_poly

#include "header.cpp"
#include "vect.cpp"
#define pol poly<cood>

// implementation clockwise oriented

tmpl struct poly {
    vector<vec> v;
    
    // constructors
    pol () {}
    pol (vector<vec> x) : v(x) {}

    // XXX destructive
    void resort () { 
        for (auto i = 1u; i < v.size(); i++)
            if (v[i] < v[0])
                swap(v[i], v[0]);
        vec anc = v[0];
        sort(v.begin() + 1, v.end(), [anc] (vec a, vec b) {
            return anc.left(a,b) == -1;
        });
    }

    // XXX destructive
    void graham () {
        resort();
        if (v.size() < 2u) 
            return;

        auto st = 0u;
        for (auto i = 1u; i < v.size(); i++) {
            while (st > 2u && v[st-2].left(v[i], v[st-1]) != -1)
                st--;
            v[st++] = v[i];
        }

        v.resize(st);
    }
};

#endif
