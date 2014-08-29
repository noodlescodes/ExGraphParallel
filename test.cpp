#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sstream>
#include "Node.h"
#include "Matrix.h"
#include "Explorer.h"

using namespace std;
using namespace VAN_MAASTRICHT;

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cout << "Need an argument for the order of the graph" << endl;
	}
	if(argc > 2) {
		cout << "Only provide one argument" << endl;
	}

	stringstream str;
	str << argv[1];
	int order;
	str >> order;

	time_t start = time(NULL);
	Matrix m = Matrix();
	m.set_size(order);
	Node n = Node(m, 0, 1, 0);
	Explorer *e = new Explorer(n);
	
	e->explore();

	delete e;

	cout << "Time taken: " << time(NULL) - start << endl;

	return 0;
}
