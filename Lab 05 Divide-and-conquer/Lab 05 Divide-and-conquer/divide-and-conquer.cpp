#include "divide-and-conquer.h"
#include <algorithm>
#include <iterator>

DivideConquer::DivideConquer() {}

DivideConquer::DivideConquer(std::vector<Point> p) {
	std::sort(p.begin(), p.end(), [](const Point& a, const Point& b) { return a.x < b.x; });
	build(p);
	
}

std::vector<Point> DivideConquer::build(std::vector <Point> p) {
	if (p.size() <= 2) return p;
	
	std::vector<Point> left;
	std::vector<Point> right;

	for (int i = 0; i < p.size(); i++) {
		if (i < p.size() / 2) {
			left.push_back(p[i]);
		}
		else {
			right.push_back(p[i]);
		}
	}

	return merge(build(left), build(right));
}

std::vector<Point> DivideConquer::merge(std::vector<Point> left, std::vector<Point> right) {
	std::vector<Point> u_tang = upper_tangent(left, right);
	std::vector<Point> l_tang = lower_tangent(left, right);
	std::vector<Point> result;

	int i = -1;
	int j = -1;
	do {
		i++;
		result.push_back(left[i]);
	} while (left[i] != u_tang[0]);
	while (right[j] != u_tang[1]) {
		j++;
	}
	do {
		j = j + 1 <= right.size() - 1 ? j + 1 : 0;
		result.push_back(right[j]);
	} while (right[j] != l_tang[1]);
	while (left[i] != l_tang[0]) {
		i++;
	}
	while (i < left.size()) {
		result.push_back(left[i]);
	}

	return result;
}

std::vector<Point> DivideConquer::upper_tangent(std::vector<Point> left, std::vector<Point> right) {
	int id_a = left.size() - 1;
	int id_b = 0;
	std::vector<Point> result;
	while (right[id_b].clockwise(left[id_a], left[(id_a + 1 > left.size() ? id_a + 1 : 0)]) >= 0) {
		id_a = (id_a + 1 > left.size() ? id_a + 1 : 0);
	}
	result.push_back(left[id_a]);
	while (left[id_a].clockwise(right[id_b], right[(id_b - 1 >= 0 ? id_b - 1 : right.size() - 1)]) <= 0) {
		id_b = (id_b - 1 >= 0 ? id_b - 1 : right.size() - 1);
	}
	result.push_back(right[id_b]);
	return result;
}

std::vector<Point> DivideConquer::lower_tangent(std::vector<Point> left, std::vector<Point> right) {
	int id_a = left.size() - 1;
	int id_b = 0;
	std::vector<Point> result;
	while (right[id_b].clockwise(left[id_a], left[(id_a + 1 > left.size() ? id_a + 1 : 0)]) <= 0) {
		id_a = (id_a + 1 > left.size() ? id_a + 1 : 0);
	}
	result.push_back(left[id_a]);
	while (left[id_a].clockwise(right[id_b], right[(id_b - 1 >= 0 ? id_b - 1 : right.size() - 1)]) >= 0) {
		id_b = (id_b - 1 >= 0 ? id_b - 1 : right.size() - 1);
	}
	result.push_back(right[id_b]);
	return result;
}