typedef long long cood;
const cood eps = 0;

#include "gtest/gtest.h"
#include "../code/geometry.cpp"

bool operator== (vec a, vec b)
{ return a.x == b.x && a.y == b.y; }

const vec sample_pointset[] = { vec(7,7), vec(8,7), vec(8,8), vec(10,7), vec(10,8), vec(11,7), vec(11,11), vec(11,9), vec(12,12), vec(13,9), vec(14,10), vec(14,9), vec(14,14), vec(15,14), vec(15,12), vec(15,11) };
const int sample_size = 16;

TEST(Graham, Simple) {
	vec *v = new vec[16];
	vec expect[] = { vec(7,7), vec(11,7), vec(14,9), vec(15,11), vec(15,14), vec(14,14) };

	for (int i = 0; i < sample_size; i++)
		v[i] = sample_pointset[i];

	EXPECT_EQ(graham(v, sample_size, 0), 6) << "Convex hull should have size 6";
	for (int i = 0; i < 6; i++)
		EXPECT_EQ(v[i], expect[i]) << "Position " << i << " of the hull should match";
}

TEST(Graham, WithBorder) {
	vec *v = new vec[16];
	vec expect[] = { vec(7,7), vec(8,7), vec(10,7), vec(11,7), vec(14,9), vec(15,11), vec(15,12), vec(15,14), vec(14,14), vec(12,12), vec(11,11), vec(8,8) };

	for (int i = 0; i < sample_size; i++)
		v[i] = sample_pointset[i];
	
	EXPECT_EQ(graham(v, sample_size, 1), 12) << "Convex hull should have size 12";
	for (int i = 0; i < 12;i ++)
		EXPECT_EQ(v[i], expect[i]) << "Position " << i << " of the hull should match";
}
