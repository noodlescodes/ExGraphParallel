#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sstream> // will eventually use this for passing parameters
#include "Node.h"
#include "Matrix.h"
#include "Explorer.h"

using namespace std;
using namespace VAN_MAASTRICHT;

int main(int argc, char* argv[]) {
	time_t start = time(NULL);
	Matrix m = Matrix();
	m.set_size(10);
	Node n = Node(m, 0, 1, 0);
	Explorer *e = new Explorer(n);
	
	e->explore();

	delete e;

	cout << "Time taken: " << time(NULL) - start << endl;

	return 0;
}
