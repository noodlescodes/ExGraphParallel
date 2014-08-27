#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sstream> // will eventually use this for passing parameters
#include "Node.h"
#include "Matrix.h"

using namespace std;
using namespace VAN_MAASTRICHT;

int main(int argc, char* argv[]) {
	time_t start = time(NULL);
	Matrix m = Matrix();
	m.set_size(3);
	cout << m << endl;

	Node *n = new Node(m, 0, 1);

	cout << n->data() << endl;

	delete n;

	cout << m << endl;

	cout << "Time taken: " << time(NULL) - start << endl;

	return 0;
}
