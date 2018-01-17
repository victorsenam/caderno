// Geogebra: https://ggbm.at/GT8w9nCV
#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll cood;
const cood eps = 0;

#include "gtest/gtest.h"
#include "../../code/geometry/basic.cpp"

bool operator != (vec a, vec b)
{ return !(a==b); }

vec C[] = {vec(30,15), vec(33,19), vec(40,20), vec(42,3)};
cir c[] = {cir(C[0],3), cir(C[1],5), cir(C[0],10), cir(C[0],14), cir(C[0],20), cir(C[3],6), cir(C[1],2)};

vec D[] = {vec(10,50), vec(3,63), vec(5,47), vec(11,43), vec(11,49), vec(10,51), vec(9,51), vec(15,50), vec(10,45), vec(0,45), vec(20,47), vec(-4,60), vec(5,55)};
cir d[] = {cir(D[0],3), cir(D[1],10)};

TEST(geometry_basic_cir, contains) {
	EXPECT_TRUE(c[0].contains(C[0])) << "Simple";
	EXPECT_FALSE(c[2].contains(C[2])) << "Simple";
	EXPECT_TRUE(c[3].contains(C[2])) << "Simple";
	EXPECT_FALSE(c[5].contains(C[2])) << "Simple";
	EXPECT_TRUE(c[1].contains(C[0])) << "Border contained";
	EXPECT_TRUE(cir(C[0],0).contains(C[0])) << "Degenerate";
	EXPECT_FALSE(cir(C[0],0).contains(C[1])) << "Degenerate";
}

TEST(geometry_basic_cir, border) {
	EXPECT_FALSE(c[0].border(C[0])) << "Simple";
	EXPECT_FALSE(c[2].border(C[2])) << "Simple";
	EXPECT_FALSE(c[3].border(C[2])) << "Simple";
	EXPECT_FALSE(c[5].border(C[2])) << "Simple";
	EXPECT_TRUE(c[1].border(C[0])) << "Border contained";
	EXPECT_TRUE(cir(C[0],0).border(C[0])) << "Degenerate";
	EXPECT_FALSE(cir(C[0],0).border(C[1])) << "Degenerate";
}

TEST(geometry_basic_cir, has_inter) {
	EXPECT_TRUE(c[0].has_inter(c[1])) << "Not contained";
	EXPECT_FALSE(c[0].has_inter(c[5])) << "No inter";
	EXPECT_TRUE(c[2].has_inter(c[3])) << "Contained";
	EXPECT_TRUE(c[1].has_inter(c[3])) << "Contained different center";
	EXPECT_TRUE(c[6].has_inter(c[0])) << "Border touch";
	EXPECT_TRUE(c[1].has_inter(c[2])) << "Contained and border touch";
	EXPECT_TRUE(c[2].has_inter(c[2])) << "Same";

	EXPECT_TRUE(c[0].has_inter(cir(C[0],0))) << "Degenerate";
	EXPECT_TRUE(cir(C[0],0).has_inter(c[0])) << "Degenerate";
	EXPECT_FALSE(c[0].has_inter(cir(C[3],0))) << "Degenerate";
	EXPECT_TRUE(cir(C[0],0).has_inter(cir(C[0],0))) << "Degenerate";
	EXPECT_FALSE(cir(C[0],0).has_inter(cir(C[3],0))) << "Degenerate";
	EXPECT_TRUE(c[1].has_inter(cir(C[0],0))) << "Degenerate";
	EXPECT_TRUE(c[3].has_inter(cir(C[2],0))) << "Degenerate";
}

TEST(geometry_basic_cir, has_border_inter) {
	EXPECT_TRUE(c[0].has_border_inter(c[1])) << "Not contained";
	EXPECT_FALSE(c[0].has_border_inter(c[5])) << "No inter";
	EXPECT_FALSE(c[2].has_border_inter(c[3])) << "Contained";
	EXPECT_FALSE(c[1].has_border_inter(c[3])) << "Contained different center";
	EXPECT_TRUE(c[6].has_border_inter(c[0])) << "Border touch";
	EXPECT_TRUE(c[1].has_border_inter(c[2])) << "Contained and border touch";
	EXPECT_TRUE(c[2].has_inter(c[2])) << "Same";

	EXPECT_FALSE(c[0].has_border_inter(cir(C[0],0))) << "Degenerate";
	EXPECT_FALSE(cir(C[0],0).has_border_inter(c[0])) << "Degenerate";
	EXPECT_FALSE(c[0].has_border_inter(cir(C[3],0))) << "Degenerate";
	EXPECT_TRUE(cir(C[0],0).has_border_inter(cir(C[0],0))) << "Degenerate";
	EXPECT_FALSE(cir(C[0],0).has_border_inter(cir(C[3],0))) << "Degenerate";
	EXPECT_TRUE(c[1].has_border_inter(cir(C[0],0))) << "Degenerate";
	EXPECT_FALSE(c[3].has_border_inter(cir(C[2],0))) << "Degenerate";
}

TEST(geometry_basic_cir, has_inter_seg) {
	EXPECT_TRUE(d[0].has_inter_seg(D[4],D[5])) << "Inside";
	EXPECT_TRUE(d[0].has_inter_seg(D[4],D[6])) << "Inside through center";
	EXPECT_TRUE(d[0].has_inter_seg(D[0],D[3])) << "Ray";
	EXPECT_TRUE(d[0].has_inter_seg(D[4],D[8])) << "Enters";
	EXPECT_TRUE(d[0].has_inter_seg(D[5],D[8])) << "Enters through center";
	EXPECT_FALSE(d[0].has_inter_seg(D[3],D[8])) << "Outside to in";
	EXPECT_FALSE(d[0].has_inter_seg(D[9],D[2])) << "Outside to in through center";
	EXPECT_TRUE(d[0].has_inter_seg(D[2],D[7])) << "Secant";
	EXPECT_TRUE(d[0].has_inter_seg(D[2],D[10])) << "Tangent";
	EXPECT_FALSE(d[0].has_inter_seg(D[3],D[10])) << "No line int";
	EXPECT_FALSE(d[1].has_inter_seg(D[4],D[6])) << "Other circle false";
	EXPECT_FALSE(d[0].has_inter_seg(D[11],D[12])) << "Far";
	EXPECT_TRUE(d[1].has_inter_seg(D[11],D[12])) << "Other circle true";
	EXPECT_FALSE(d[0].has_inter_seg(D[10],D[9]));

	EXPECT_TRUE(d[0].has_inter_seg(D[0],D[0])) << "Degenerate";
	EXPECT_TRUE(d[0].has_inter_seg(D[4],D[4])) << "Degenerate";
	EXPECT_FALSE(d[0].has_inter_seg(D[7],D[7])) << "Degenerate";
}

TEST(geometry_basic_cir, has_inter_lin) {
	EXPECT_TRUE(d[0].has_inter_lin(D[4],D[5])) << "Inside";
	EXPECT_TRUE(d[0].has_inter_lin(D[4],D[6])) << "Inside through center";
	EXPECT_TRUE(d[0].has_inter_lin(D[0],D[3])) << "Ray";
	EXPECT_TRUE(d[0].has_inter_lin(D[4],D[8])) << "Enters";
	EXPECT_TRUE(d[0].has_inter_lin(D[5],D[8])) << "Enters through center";
	EXPECT_TRUE(d[0].has_inter_lin(D[3],D[8])) << "Outside to in";
	EXPECT_TRUE(d[0].has_inter_lin(D[9],D[2])) << "Outside to in through center";
	EXPECT_TRUE(d[0].has_inter_lin(D[2],D[7])) << "Secant";
	EXPECT_TRUE(d[0].has_inter_lin(D[2],D[10])) << "Tangent";
	EXPECT_FALSE(d[0].has_inter_lin(D[3],D[10])) << "No line int";
	EXPECT_TRUE(d[1].has_inter_lin(D[4],D[6])) << "Other circle false";
	EXPECT_TRUE(d[0].has_inter_lin(D[11],D[12])) << "Far";
	EXPECT_TRUE(d[1].has_inter_lin(D[11],D[12])) << "Other circle true";

	EXPECT_TRUE(d[0].has_inter_lin(D[0],D[0])) << "Degenerate";
	EXPECT_TRUE(d[0].has_inter_lin(D[4],D[4])) << "Degenerate";
	EXPECT_FALSE(d[0].has_inter_lin(D[7],D[7])) << "Degenerate";

	EXPECT_FALSE(d[0].has_inter_lin(D[3],D[7]));
	EXPECT_FALSE(d[1].has_inter_lin(D[2],D[9]));
	EXPECT_FALSE(d[0].has_inter_lin(D[10],D[9]));
}
