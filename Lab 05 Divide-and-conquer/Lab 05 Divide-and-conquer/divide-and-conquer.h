#pragma once
#include <vector>
#include "point.h"

class DivideConquer
{
public:
	DivideConquer();
	DivideConquer(std::vector<Point>);
	void print();
	~DivideConquer();

private:
	std::vector<Point> hull;
	std::vector<Point> build(std::vector<Point>);
	std::vector<Point> merge(std::vector<Point>, std::vector <Point>);
	std::vector<Point> upper_tangent(std::vector<Point>, std::vector<Point>);
	std::vector<Point> lower_tangent(std::vector<Point>, std::vector<Point>);
};


