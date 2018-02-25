#include "divide-and-conquer.h"

DivideConquer::DivideConquer() {}

DivideConquer::DivideConquer(std::vector<Point> p) {
	std::sort(p.begin(), p.end(), [](const Point& a, const Point& b) { return a.x < b.x; });
	hull = build(p);
}

void DivideConquer::print() {
	std::cout << "Convex hull contains: \n";
	for (int i = 0; i < hull.size(); i++) {
		std::cout << hull[i].x << " " << hull[i].y << "\n";
	}
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
	int j = 0;
	do {
		i++;
		result.push_back(left[i]);
	} while (left[i] != u_tang[0]);
	if (right.size() > 1) {
		while (right[j] != u_tang[1]) {
			j++;
		}
		do {
			result.push_back(right[j]);
			j = j + 1 < right.size() ? j + 1 : 0;
		} while (right[j] != l_tang[1]);
		result.push_back(right[j]);
	}
	else {
		result.push_back(right[0]);
	}
	if (left.size() > 1) { 
		while (left[i] != l_tang[0]) {
			i++;
			if (i == left.size()) return result;
		}
		while (i < left.size()) {
			result.push_back(left[i]);
			i++;
		}
	}
	return result;
}

std::vector<Point> DivideConquer::upper_tangent(std::vector<Point> left, std::vector<Point> right) {
	int id_a = left.size() - 1;
	int id_b = 0;
	for (int i = 0; i < left.size(); i++) {
		if (left[i].x > left[id_a].x) id_a = i;
	}
	for (int i = 0; i < right.size(); i++) {
		if (right[i].x < right[id_b].x) id_b = i;
	}
	
	std::vector<Point> result;
	while (left[id_a].clockwise(left[(id_a - 1 >= 0 ? id_a - 1 : left.size() - 1)], right[id_b]) < 0 && left.size() != 1) {
		id_a = (id_a - 1 >= 0 ? id_a - 1 : left.size() - 1);
	}
	result.push_back(left[id_a]);
	while (right[id_b].clockwise(left[id_a], right[(id_b + 1 < right.size() ? id_b + 1 : 0)]) < 0 && right.size() != 1) {
		id_b = (id_b + 1 < right.size() ? id_b + 1 : 0);
	}
	result.push_back(right[id_b]);
	return result;
}

std::vector<Point> DivideConquer::lower_tangent(std::vector<Point> left, std::vector<Point> right) {
	int id_a = left.size() - 1;
	int id_b = 0;
	std::vector<Point> result;
	while (left[id_a].clockwise(left[(id_a + 1 > left.size() ? id_a + 1 : 0)] , right[id_b]) > 0 && left.size() != 1) {
		id_a = (id_a + 1 < left.size() ? id_a + 1 : 0);
	}
	result.push_back(left[id_a]);
	while (right[id_b].clockwise(left[id_a], right[(id_b - 1 >= 0 ? id_b - 1 : right.size() - 1)]) > 0 && right.size()!= 1) {
		id_b = (id_b - 1 >= 0 ? id_b - 1 : right.size() - 1);
	}
	result.push_back(right[id_b]);
	return result;
}

DivideConquer::~DivideConquer() {}