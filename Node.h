#ifndef NATHAN_VAN_MAASTRICHT_NODE
#define NATHAN_VAN_MAASTRICHT_NODE

#include "Matrix.h"

namespace VAN_MAASTRICHT {
	class Node {
	public:
		Node(const Matrix& init_data = Matrix(), const int i0 = 0, int j0 = 1, int depth0 = 0) {
			data_field = init_data;
			i = i0;
			j = j0;
			depth = depth0;
		}

		Matrix& data() {return data_field;}
		const Matrix& data() const {return data_field;}
		void set_data(const Matrix& init_data) {data_field = init_data;}
		int get_depth() {return depth;}
		int get_i() {return i;}
		int get_j() {return j;}

	private:
		Matrix data_field;
		int i, j;
		int depth;
	};
}
#endif
