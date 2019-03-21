#include <iostream>
#include "Eigen/Dense"
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>

using namespace std;
using namespace Eigen;

int main() {
    MatrixXd m(3,3);
    m << 1,2,3,4,5,6,7,8,9;
    cout << m << endl;
    RowVectorXd v = m.colwise().mean();
    cout << v << endl;
    cout << m.rowwise() - v << endl;
    cout << m.adjoint() << endl;
    cout << m.transpose() << endl;
    cout << m.transpose() * m << endl;
    cout << m / 2 << endl;
    EigenSolver<MatrixXd> eigensolver(m);
    cout << eigensolver.pseudoEigenvalueMatrix() << endl;
    cout << eigensolver.pseudoEigenvectors() << endl;
    cout << Success << endl;
    SelfAdjointEigenSolver<MatrixXd> es(m);
    cout << es.eigenvectors() << endl;
    cout << es.eigenvalues() << endl;
    cout << m.sum() << endl;
    return 0;
}