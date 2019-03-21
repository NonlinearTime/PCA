//
// Created by haines on 3/20/19.
//

#include "PCA.h"

//a column means a example
void PCA::normalize() {
    RowVectorXd mean_val_row = data.colwise().mean();
    data.rowwise() -= mean_val_row;
}

//calculate the covariance of data
void PCA::covariance() {
    cov = data.transpose() * data;
    cov = cov / (data.rows() - 1);
}

//calculate the eigen vectors and eigen values of covariance
void PCA::eigen() {
    EigenSolver<MatrixXd> eigensolver(cov);
    if (eigensolver.info() != Success) abort();
    eigen_vectors = eigensolver.pseudoEigenvectors();
    eigen_values_matrix = eigensolver.pseudoEigenvalueMatrix();
}



void PCA::set_max_component() {
    double sum = 0;
    double tot_sum = eigen_values_matrix.sum();
    uint32_t cnt = 0;
    for (int i = 0 ; i != eigen_values_matrix.rows(); ++i) {
        sum += eigen_values_matrix(i, i);
        cnt++;
        if (sum / tot_sum < threshold) break;
    }
    max_components = cnt;
}

void PCA::sort_eigenvectors() {
    map<double, int> eigen_map;
    int D_rows = eigen_values_matrix.rows();
    int V_rows = eigen_vectors.rows();
    double *evectors = new double(D_rows * D_rows);
    double *evalues = new double(D_rows);
    for (int i = 0; i < V_rows; ++i) {
        for (int j = 0 ; j < V_rows ; ++i) {
            evectors[i * V_rows + j] = eigen_vectors(j, i);
        }
    }
    for (int i = 0 ; i != D_rows; ++i) {
        evalues[i] = eigen_values_matrix(i, i);
        eigen_map.insert(make_pair(evalues[i], i));
    }

    auto iter = eigen_map.rbegin();
    for (int i = 0; iter != eigen_map.rend(), i != D_rows; ++i, ++iter) {
        eigen_values_matrix(i, i) = iter->first;
        for (int j = 0 ; j != D_rows ; ++j) {
            eigen_vectors(j, i) = evectors[j + D_rows * iter->second];
        }
    }

    delete [] evectors;
    delete [] evalues;

}

void PCA::project() {
    MatrixXd P = eigen_vectors.leftCols(max_components);
    result = P.transpose() * data;
}

void PCA::back_project(MatrixXd mat, MatrixXd eigen_vectors) {
    MatrixXd P = eigen_vectors.transpose();
    MatrixXd P_inverse = P.inverse();
    MatrixXd raw_data = P_inverse * mat;
}

const MatrixXd &PCA::getData() const {
    return data;
}

void PCA::setData(const MatrixXd &data) {
    PCA::data = data;
}

const MatrixXd &PCA::getCov() const {
    return cov;
}

const MatrixXd &PCA::getEigen_vectors() const {
    return eigen_vectors;
}

const MatrixXd &PCA::getEigen_values_matrix() const {
    return eigen_values_matrix;
}

const MatrixXd &PCA::getResult() const {
    return result;
}

double PCA::getThreshold() const {
    return threshold;
}

void PCA::setThreshold(double threshold) {
    PCA::threshold = threshold;
}













