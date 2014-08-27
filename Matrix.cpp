#include "Matrix.h"

namespace VAN_MAASTRICHT {
	Matrix::Matrix(const vector<vector<int> > mat) {
		matrix = mat;
		s = mat.size();
		number_edges = 0;
		for(unsigned int i = 0; i < s; i++) {
			for(unsigned int j = 0; j < s; j++) {
				if(matrix[i][j] == 1) {
					number_edges++;
				}
			}
		}
		degree = vector<unsigned int>(s);
		for(unsigned int i = 0; i < s; i++) {
			for(unsigned int j = 0; j < s; j++) {
				degree[i] += matrix[i][j];
			}
		}
	}

	Matrix::~Matrix() {
		matrix.clear();
	}

	int Matrix::set_entry(unsigned int i, unsigned int j, int data) {
		if((i >= matrix.size()) || (j >= matrix.size())) {
			return -1;
		}
		else {
			if((matrix[i][j] == 0) && (data == 1) ) {
				number_edges++;
				degree[i]++;
			}
			else if((matrix[i][j] ==  1) && (data == 0)) {
				number_edges--;
				degree[i]--;
			}
			matrix[i][j] = data;
		}

		return 1;
	}
	
	int Matrix::set_entry_symm(unsigned int i, unsigned int j, int data) {
		if(set_entry(i, j, data) + set_entry(j, i, data) < 1) {
			return -1;
		}

		return 1;
	}

	void Matrix::set_matrix(const vector<vector<int> > mat) {
		matrix = mat;
		degree.resize(matrix.size());
		for(unsigned int i = 0; i < degree.size(); i++) {
			degree[i] = 0;
			for(unsigned int j = 0; j < degree.size(); j++) {
				degree[i] += matrix[i][j];
			}
		}
	}

	void Matrix::set_size(const int size) {
		matrix.resize(size);
		for(unsigned int i = 0; i < matrix.size(); i++) {
			matrix[i].resize(size);
		}
		s = size;
		degree.resize(size);
	}

	const int Matrix::trace() const {
		int trace = 0;
		for(unsigned int i = 0; i < matrix.size(); i++) {
			trace += matrix[i][i];
		}
		return trace;
	}

	const unsigned int Matrix::size() const {
		return s;
	}

	int Matrix::get_entry(unsigned int i, unsigned int j) {
		if((i >= matrix.size()) || j >= matrix.size()) {
			return -1;
		}
		return matrix[i][j];
	}

	const int Matrix::get_entry(unsigned int i, unsigned int j) const {
		if((i >= matrix.size()) || j >= matrix.size()) {
			return -1;
		}
		return matrix[i][j];		
	}

	unsigned int Matrix::get_number_edges() {
		return number_edges;
	}

	const unsigned int Matrix::get_number_edges() const {
		return number_edges;
	}

	unsigned int Matrix::get_degree(unsigned int i) {
		if(i >= matrix.size()) {
			return 0; // can't think of anything better to return
		}
		return degree[i];
	}

	const unsigned int Matrix::get_degree(unsigned int i) const {
		return degree[i];
	}

	ostream& operator <<(ostream& outs, const Matrix& mat) {
		for(unsigned int i = 0; i < mat.size(); i++) {
			for(unsigned int j = 0; j < mat.size(); j++) {
				outs << mat.get_entry(i, j) << ", ";
			}
			outs << endl;
		}

		return outs;
	}

	Matrix operator +(const Matrix& m1, const Matrix& m2) {
		if(m1.size() != m2.size()) {
			return Matrix();
		}
		vector<vector<int> > mat = vector<vector<int> >(m1.size());
		for(unsigned int i = 0; i < mat.size(); i++) {
			mat[i].resize(mat.size());
		}
		for(unsigned int i = 0; i < mat.size(); i++) {
			for(unsigned int j = 0; j < mat.size(); j++) {
				mat[i][j] = m1.get_entry(i, j) + m2.get_entry(i, j);
			}
		}

		return Matrix(mat);
	}

	Matrix operator *(const Matrix& m1, const Matrix& m2) {
		if(m1.size() != m2.size()) {
			return Matrix();
		}
		vector<vector<int> > mat = vector<vector<int> >(m1.size());
		for(unsigned int i = 0; i < mat.size(); i++) {
			mat[i].resize(mat.size());
		}
		for(unsigned int i = 0; i < mat.size(); i++) {
			for(unsigned int j = 0; j < mat.size(); j++) {
				for(unsigned int k = 0; k < mat.size(); k++) {
					mat[i][j] += m1.get_entry(i, k) * m2.get_entry(k, j);
				}
			}
		}

		return Matrix(mat);
	}

	Matrix operator %(const Matrix& m1, const Matrix& m2) {
		if(m1.size() != m2.size()) {
			return Matrix();
		}
		vector<vector<int> > mat = vector<vector<int> >(m1.size());
		for(unsigned int i = 0; i < mat.size(); i++) {
			mat[i].resize(mat.size());
		}
		for(unsigned int i = 0; i < mat.size(); i++) {
			for(unsigned int j = 0; j < mat.size(); j++) {
				mat[i][j] = m1.get_entry(i, j) * m2.get_entry(i, j);
			}
		}

		return Matrix(mat);
	}
}
