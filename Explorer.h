#ifndef NATHAN_VAN_MAASTRICHT_EXPLORER
#define NATHAN_VAN_MAASTRICHT_EXPLORER

#include <stack>
#include "Node.h"
#include "Matrix.h"

using VAN_MAASTRICHT::Node;
using VAN_MAASTRICHT::Matrix;

namespace VAN_MAASTRICHT {
	class Explorer {
	public:
		Explorer(Node node);

		// getters
		unsigned long long get_number_solutions();
		
		// setters
		void add_node(Node node);

		// modifers
		void explore();
		void generate_children(Node node, unsigned int i, unsigned int j);

		// exploring specific
		bool continue_heuristics(const Matrix &m, int depth);
		bool degree_sat(const Matrix &m);
		bool check_valid(const Matrix &m);
		bool symmetric(const Matrix &m);
		bool triangles_exist(const Matrix &m);
		bool squares_exist(const Matrix &m);
		
	private:
		void max_edges_set(); //sets the max_edges_array

		stack<Node> nodes_to_process;
		double explored;
		double max_to_explore;
		unsigned long long number_of_solutions;
		double print_check; // does not give arbitarily large amounts of money, unfortunately.
		unsigned int max_edges;
		unsigned int max_depth;
		unsigned int max_degree;
		unsigned int min_degree;
		double print_inc;
		vector<unsigned int> max_edges_array;
	};
}
#endif
