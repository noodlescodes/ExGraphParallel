#include "Explorer.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

namespace VAN_MAASTRICHT {
	// make sure to pass in a matrix that has size > 0
	Explorer::Explorer(Node node) {
		max_edges_set();
		add_node(node);
		explored = 1;
		number_of_solutions = 0;
		print_inc = pow(10, 5);
		print_check = print_inc;
		min_degree = max_edges_array[node.data().size()] - max_edges_array[node.data().size() - 1];
		max_degree = node.data().size() - 1 * node.data().size() / 2;
		max_edges = 2 * max_edges_array[node.data().size()];
		max_depth = (node.data().size() - 1) * node.data().size() / 2;
		max_to_explore = pow(2, max_depth);
		cout << "Max to explore: " << max_to_explore << endl;
		
	}

	void Explorer::max_edges_set() {
		max_edges_array.push_back(0); // 0
		max_edges_array.push_back(0); // 1
		max_edges_array.push_back(1); // 2
		max_edges_array.push_back(2); // 3
		max_edges_array.push_back(3); // 4
		max_edges_array.push_back(5); // 5
		max_edges_array.push_back(6); // 6
		max_edges_array.push_back(8); // 7
		max_edges_array.push_back(10); // 8
		max_edges_array.push_back(12); // 9
		max_edges_array.push_back(15); // 10
		max_edges_array.push_back(16); // 11
		max_edges_array.push_back(18); // 12
		max_edges_array.push_back(21); // 13
		max_edges_array.push_back(23); // 14
		max_edges_array.push_back(26); // 15
		max_edges_array.push_back(28); // 16
		max_edges_array.push_back(31); // 17
		max_edges_array.push_back(34); // 18
		max_edges_array.push_back(38); // 19
		max_edges_array.push_back(41); // 20
		max_edges_array.push_back(44); // 21
		max_edges_array.push_back(47); // 22
		max_edges_array.push_back(50); // 23
		max_edges_array.push_back(54); // 24
		max_edges_array.push_back(57); // 25
		max_edges_array.push_back(61); // 26
		max_edges_array.push_back(65); // 27
		max_edges_array.push_back(68); // 28
		max_edges_array.push_back(72); // 29
		max_edges_array.push_back(76); // 30
		max_edges_array.push_back(80); // 31
		max_edges_array.push_back(85); // 32
		max_edges_array.push_back(88); // 33
	}

	void Explorer::explore() {
		while(number_of_solutions == 0) {
			Node node = nodes_to_process.front();
			nodes_to_process.pop();
			if(check_valid(node.data()) && continue_heuristics(node.data(), node.get_depth())) {
				int size = node.data().size();
				if((node.get_i() * size + node.get_j()) < (size * size)) {
					explored++;
					generate_children(node, node.get_i(), node.get_j());
				}
				else if(max_edges == node.data().get_number_edges()) {
					cout << "edges: " << node.data().get_number_edges() / 2 << endl;
					cout << "depth: " << node.get_depth() << endl;
					cout << node.data() << endl;
					number_of_solutions++;
				}
			}
			else {
				explored += pow(1, max_depth - node.get_depth()) - 1;
			}
			if(explored > print_check && number_of_solutions < 1) {
				cout << "Explored: " << explored << " / " << max_to_explore << " | " << explored / max_to_explore * 100 << "%" << endl;
				cout << "Number solutions: " << number_of_solutions << endl;
				print_check += print_inc;
			}
		}
	}

	void Explorer::generate_children(Node node, unsigned int i, unsigned int j) {
		int j_d = (j + 1) % node.data().size();
		int i_d = i;
		if(j_d == 0) {
			i_d++;
			j_d = i_d + 1;
		}
		Node n0 = Node(node.data(), i_d, j_d, node.get_depth() + 1);
		Matrix m = node.data();
		m.set_entry_symm(i_d, j_d, 1);
		Node n1 = Node(m, i_d, j_d, node.get_depth() + 1);
		add_node(n0);
		add_node(n1);
	}

	unsigned long long Explorer::get_number_solutions() {
		return number_of_solutions;
	}

	void Explorer::add_node(Node node) {
		nodes_to_process.push(node);
	}

	bool Explorer::continue_heuristics(const Matrix &m, int depth) {
		if(max_edges < m.get_number_edges()) {
			return false;
		}
		if(max_depth - depth + 2 < max_edges - m.get_number_edges()) {
			return false;
		}
		if(!degree_sat(m)) {
			return false;
		}
		
		return true;
	}

	bool Explorer::degree_sat(const Matrix &m) {
		for(unsigned int i = 0; i < m.size(); i++) {
			if(max_degree < m.get_degree(i)) {
				return false;
			}
		}

		return true;
	}

	bool Explorer::check_valid(const Matrix &m) {
		if(m.get_number_edges() == 0) {
			return true;
		}
		if(triangles_exist(m)) {	
			return false;
		}
		if(squares_exist(m)) {
			return false;
		}
		return true;
	}

	bool Explorer::symmetric(const Matrix &m) {
		bool sym = true;
		for(unsigned int i = 0; i < m.size(); i++) {
			for(unsigned int j = 0; j < m.size(); j++) {
				if(m.get_entry(i, j) != m.get_entry(j, i)) {
					sym = false;
					break;
				}
			}
			if(!sym) {
				break;
			}
		}
		return sym;
	}

	bool Explorer::triangles_exist(const Matrix &m) {
		Matrix mm = m * m;
		Matrix mmm = m * mm;
		if(mmm.trace() == 0) {
			return false;
		}
		return true;
	}

	bool Explorer::squares_exist(const Matrix &m) {
		Matrix mm = m * m;
		Matrix mmmm = mm * mm;
		int sum = mmmm.trace();
		for(unsigned int i = 0; i < m.size(); i++) {
			for(unsigned int j = 0; j < m.size(); j++) {
				sum -= mm.get_entry(i, j);
			}
		}
		for(unsigned int i = 0; i < m.size(); i++) {
			if(m.get_degree(i) > 1) {
				sum -= m.get_degree(i) * (m.get_degree(i) - 1);
			}
		}

		if(sum == 0) {
			return false;
		}

		return true;
	}
}
