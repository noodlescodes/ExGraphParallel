#ifndef NATHAN_VAN_MAASTRICHT_MATRIX
#define NATHAN_VAN_MAASTRICHT_MATRIX

#include <vector>
#include <cstdlib>
#include <ostream>

using namespace std;

namespace VAN_MAASTRICHT {
	class Matrix {
	public:
		// constructor
		Matrix(const vector<vector<int> > mat = vector<vector<int> >());
		~Matrix();

		// modification functions
		int set_entry(unsigned int i, unsigned int j, int data);
		int set_entry_symm(unsigned int i, unsigned int j, int data);
		void set_matrix(const vector<vector<int> > mat);
		void set_size(const int size);

		// constant member functions
		const int trace() const;
		const unsigned int size() const;
		int get_entry(unsigned int i, unsigned int k);
		const int get_entry(unsigned int i, unsigned int k) const;
		unsigned int get_number_edges();
		const unsigned int get_number_edges() const;
		unsigned int get_degree(unsigned int i);
		const unsigned int get_degree(unsigned int i) const;
	
	private:
		vector<vector<int> > matrix;
		unsigned int s;
		unsigned int number_edges;
		vector<unsigned int> degree;
	};
	// overloaded operators
	ostream& operator <<(ostream& outs, const Matrix& mat);
	Matrix operator +(const Matrix& m1, const Matrix& m2);
	Matrix operator *(const Matrix& m1, const Matrix& m2);
	Matrix operator %(const Matrix& m1, const Matrix& m2); // hadamard product
}
#endif
