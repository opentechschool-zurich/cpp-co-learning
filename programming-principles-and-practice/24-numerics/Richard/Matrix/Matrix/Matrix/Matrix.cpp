#include "stdafx.h"
#include "Matrix.h"
#include "MatrixIO.h"
#include <iostream>
#include <exception>

typedef Numeric_lib::Matrix<double, 2> Matrix;
typedef Numeric_lib::Matrix<double, 1> Vector;

using Numeric_lib::Index;

class Elim_failure {};
class Back_subst_failure {};

void classical_elimination(Matrix& A, Vector& b)
{
	const Index n = A.dim1();

	// traverse from 1st column to the next-to-last
	// filling zeros into all elements under the diagonal:
	for (Index col = 0; col<n - 1; ++col) {
		const double pivot = A(col, col);
		if (pivot == 0) throw Elim_failure();

		// fill zeros into each element under the diagonal of the ith row:
		for (Index row = col + 1; row<n; ++row) {
			const double mult = A(row, col) / pivot;
			A[row].slice(col) = Numeric_lib::scale_and_add(A[col].slice(col), - mult, A[row].slice(col));
			b(row) -= mult*b(col); // make the corresponding change to b
		}
	}
}

Vector back_substitution(const Matrix& A, const Vector& b)
{
	const Index n = A.dim1();
	Vector x(n);

	for (Index i = n-1; i >= 0; --i) {
		double s = b(i) - dot_product(A[i].slice(i + 1), x.slice(i + 1));

		if (double m = A(i, i))
			x(i) = s / m;
		else
			throw Back_subst_failure();
	}

	return x;
}


int main()
{
	Matrix A(2,2);
	Vector b(2);

	A(0, 0) = 1.0;
	A(0, 1) = 2.0;
	A(1, 0) = 3.0;
	A(1, 1) = 2.0;

	b(0) = 2.0;
	b(1) = 1.0;

	std::cout << "Matrix A:" << std::endl << A << std::endl;
	std::cout << "Matrix b:" << std::endl << b << std::endl;
	classical_elimination(A, b);
	std::cout << "Matrix A:" << std::endl << A << std::endl;
	std::cout << "Matrix b:" << std::endl << b << std::endl;

	Vector x = back_substitution(A, b);
	std::cout << "Vector x:" << std::endl << x << std::endl;
	return 0;
}

