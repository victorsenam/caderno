#define COOD_TYPE dbl

#include "gtest/gtest.h"
#include "../code/geometry.cpp"

TEST(geometry_vec_dbl, Comparsions) { 
    EXPECT_EQ(vec(0, 7), vec(9e-10, 7+9e-10));
    EXPECT_LT(vec(1e-9, 0), vec(2.1e-9, 0));
    EXPECT_LT(vec(0, 1e-9), vec(0, 2.1e-9));
}

TEST(geometry_vec_dbl, Rotate) {
    EXPECT_EQ(vec(1,0).rotate(0), vec(1,0));
    EXPECT_EQ(vec(1,0).rotate(.5*pi), vec(0,1));
    EXPECT_EQ(vec(1,0).rotate(pi), vec(-1,0));
    EXPECT_EQ(vec(1,0).rotate(1.5*pi), vec(0,-1));
    EXPECT_EQ(vec(1,0).rotate(2*pi), vec(1,0));

    EXPECT_EQ(vec(1,0).rotate(.25*pi), vec(sqrt(.5), sqrt(.5)));
    EXPECT_EQ(vec(416.942431806166155,466.834976408843204).rotate(1.728496650520573), vec(-526.521805830923995, 338.453356644054281));
}

TEST(geometry_vec_dbl_STRESS, RotateAndCompare) {
    // generates a random ancho
    // generates random points
    // sorts them by the anchor two different ways
    // compares the results
    mt19937_64 gen(42);
    uniform_int_distribution<int> rnd_size(100, 1000);
    uniform_real_distribution<double> rnd_module(1e-4, 1e3);
    uniform_real_distribution<double> rnd_angle(0., 2.*pi);

    int tc = 50;
    while (tc--) {
        int n = rnd_size(gen); int m = rnd_size(gen);
        if (n > m) swap(n, m);

        vec anc = (vec(1.,0.).rotate(rnd_angle(gen)));
        vec comp_anc = anc*rnd_module(gen);

        vector<double> angles(n);
        uniform_int_distribution<int> rnd_angle_idx(0, n-1);

        for (int i = 0; i < n; i++)
            angles[i] = rnd_angle(gen);

        vector<pair<double, double> > generated(m);
        vector<vec> inp(m);
        for (int i = 0; i < m; i++) {
            generated[i] = pair<double,double>(rnd_angle_idx(gen), rnd_module(gen));
            generated[i].first = .5*pi;
            inp[i] = (vec(anc).rotate(generated[i].first))*generated[i].second;
        }
        sort(inp.begin(), inp.end(), [comp_anc] (vec a, vec b) {
            return a.compare(b, comp_anc);
        });

        sort(generated.begin(), generated.end());
        for (int i = 0; i < m; i++) {
            vec cur = (vec(anc).rotate(generated[i].first)*generated[i].second);
            ASSERT_EQ(inp[i], cur);
        }
    }
}
