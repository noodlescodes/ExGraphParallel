#ifndef NATHAN_VAN_MAASTRICHT_NODE
#define NATHAN_VAN_MAASTRICHT_NODE

#include "Matrix.h"

namespace VAN_MAASTRICHT {
	class Node {
	public:
		Node(const Matrix& init_data = Matrix(), const int i0 = 0, int j0 = 1) {
			data_field = init_data;
			i = i0;
			j = j0;
		}

		Matrix& data() {return data_field;}
		const Matrix& data() const {return data_field;}
		void set_data(const Matrix& init_data) {data_field = init_data;}

	private:
		Matrix data_field;
		int i, j;
	};
}
#endif
