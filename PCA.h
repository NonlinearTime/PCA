//
// Created by haines on 3/20/19.
//

#ifndef PCA_PCA_H
#define PCA_PCA_H

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include "Eigen/Dense"
#include <map>

using namespace std;
using namespace Eigen;

class PCA {
    MatrixXd data;
    double threshold;
public:
    double getThreshold() const;

    void setThreshold();

public:
    const MatrixXd &getData() const;

    void setData(const MatrixXd &data);

    const MatrixXd &getCov() const;

    const MatrixXd &getEigen_vectors() const;

    const MatrixXd &getEigen_values_matrix() const;

    const MatrixXd &getResult() const;

private:
    MatrixXd cov;
    MatrixXd eigen_vectors;
    MatrixXd eigen_values_matrix;
    MatrixXd result;
    uint32_t max_components;


public:
    PCA();
    ~PCA();

    void normalize();
    void covariance();
    void eigen();
    void sort_eigenvectors();
    void set_max_component(double threshold);

    void project();
    void back_project(MatrixXd mat, MatrixXd eigen_vectors);


private:


};


#endif //PCA_PCA_H
