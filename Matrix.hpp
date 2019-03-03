#ifndef MATRIX_HPP

#define  MATRIX_HPP

#include <vector>
#include <iostream>
#include <cmath>


const double epsilon = 0.0000000005;

class Matrix
{
public:
	class Row
	{
	private:
		friend class Matrix;
		Row(Matrix& parent,int row);
		Matrix&	_m_parent;
		int 	_m_row;
	public:
		double &operator[](int col);
	};
    Matrix(Matrix&);
    Matrix(int row, int col);
   	Matrix(std::vector<std::vector<double>>);
    bool    operator==(const Matrix&)const;
    Matrix  &operator=(const Matrix&);
    Matrix  operator+(const Matrix&);
    Matrix  operator-(const Matrix&);
    Matrix  operator*(const Matrix&);
    Matrix  operator*(const double&);
	Row		operator[](int row);
	const int 	getSizeRows()const;
	const int 	getSizeColomn()const;

	double  determinant();
    Matrix  inverse();
    Matrix  transpose();

    void    setMatrix(const std::vector<std::vector<double>>&);
    std::vector<std::vector<double>> getMatrix()const;
    void    print();


private:
    std::vector<std::vector<double>> matrix;
    double det(std::vector<std::vector<double>> m, int size);
	std::vector<std::vector<double>> getCofactor(std::vector<std::vector<double>> m, int n, int size);
    std::vector<std::vector<double>> getCofactorInverse(std::vector<std::vector<double>> m, int y, int x, int size);

};




#endif