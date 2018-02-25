#include "divide-and-conquer.h"

int main() {
	int n;
	std::vector<Point> p;
	std::cout << "Enter number of points: ";
	std::cin >> n;
	p.resize(n);
	std::cout << "Enter points(x,y):\n";
	for (int i = 0; i < n; i++) {
		std::cin >> p[i].x >> p[i].y;
	}
	
	DivideConquer convex_hull(p);
	convex_hull.print();

	system("pause");
	return 0;
}