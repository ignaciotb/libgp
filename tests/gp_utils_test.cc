//
// libgp - Gaussian Process library for Machine Learning
// Copyright (C) 2010 Universität Freiburg
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <Eigen/Dense>
#include <gtest/gtest.h>
#include "gp_utils.h"
#include <algorithm>

TEST(Utils, randn) {
  // Kolmogorow-Smirnow-Test
  int n = 10e5;
  double D = 0.0;
  std::vector<double> array;
  for (int i=0; i<n; ++i) array.push_back(libgp::randn());
  std::sort(array.begin(), array.end());
  for (int i=0; i<n; ++i) {
    double F = libgp::cdf_norm(array[i]);
    D = std::max(D, std::max(F-(i-1.0)/n, 1.0*i/n-F));
  }
  ASSERT_GT(1.63/sqrt(n), D);
}

TEST(Utils, randperm) {
  // number of samples
  int m = 10e5;
  // number of categories
  int n=31;
  Eigen::MatrixXd count(n,n);
  count.setZero();
  int fails = 0;
  double np = 1.0*m/n;
  count.setZero();
  for (int i=0; i<m; ++i) {
    int * array = libgp::randperm(n);
    for (int j=0; j<n; ++j) {
      count(j, array[j]) += 1; 
    }
    delete[] array;
  }
  for (int i=0; i<n; ++i) {  
    // chi-square test
    double V = 0.0;
    for (int j=0; j<n; ++j) V += pow(count(j, i) - np, 2) / np;
    if (18.49 > V || 43.77 < V) fails++;
  }
  
  ASSERT_GE(10, fails);
}

TEST(Utils, randi) {
  // number of samples
  int m = 10e6;
  // number of categories
  int n=31;
  // number of iterations
  int k=30;
  Eigen::VectorXd count(n);
  int fails = 0;
  double np = 1.0*m/n;
  for (int j=0; j<k; ++j) {
    count.setZero();
    for (int i=0; i<m; ++i) count(libgp::randi(n)) += 1;
    // chi-square test
    double V = 0.0;
    for (int i=0; i<n; ++i) V += pow(count(i) - np, 2) / np;
    if (18.49 > V || 43.77 < V) fails++;
  }
  ASSERT_GE(10, fails);
}

TEST(Utils, cdf_norm) {
  double err = 10e-16;
  ASSERT_NEAR(0.000000000000000622, libgp::cdf_norm(-8.00), err);
  ASSERT_NEAR(0.000000000000004595, libgp::cdf_norm(-7.75), err);
  ASSERT_NEAR(0.000000000000031909, libgp::cdf_norm(-7.50), err);
  ASSERT_NEAR(0.000000000000208386, libgp::cdf_norm(-7.25), err);
  ASSERT_NEAR(0.000000000001279813, libgp::cdf_norm(-7.00), err);
  ASSERT_NEAR(0.000000000007392258, libgp::cdf_norm(-6.75), err);
  ASSERT_NEAR(0.000000000040160006, libgp::cdf_norm(-6.50), err);
  ASSERT_NEAR(0.000000000205226343, libgp::cdf_norm(-6.25), err);
  ASSERT_NEAR(0.000000000986587645, libgp::cdf_norm(-6.00), err);
  ASSERT_NEAR(0.000000004462172454, libgp::cdf_norm(-5.75), err);
  ASSERT_NEAR(0.000000018989562466, libgp::cdf_norm(-5.50), err);
  ASSERT_NEAR(0.000000076049605165, libgp::cdf_norm(-5.25), err);
  ASSERT_NEAR(0.000000286651571879, libgp::cdf_norm(-5.00), err);
  ASSERT_NEAR(0.000001017083242569, libgp::cdf_norm(-4.75), err);
  ASSERT_NEAR(0.000003397673124730, libgp::cdf_norm(-4.50), err);
  ASSERT_NEAR(0.000010688525774934, libgp::cdf_norm(-4.25), err);
  ASSERT_NEAR(0.000031671241833120, libgp::cdf_norm(-4.00), err);
  ASSERT_NEAR(0.000088417285200804, libgp::cdf_norm(-3.75), err);
  ASSERT_NEAR(0.000232629079035525, libgp::cdf_norm(-3.50), err);
  ASSERT_NEAR(0.000577025042390767, libgp::cdf_norm(-3.25), err);
  ASSERT_NEAR(0.001349898031630096, libgp::cdf_norm(-3.00), err);
  ASSERT_NEAR(0.002979763235054556, libgp::cdf_norm(-2.75), err);
  ASSERT_NEAR(0.006209665325776138, libgp::cdf_norm(-2.50), err);
  ASSERT_NEAR(0.012224472655044704, libgp::cdf_norm(-2.25), err);
  ASSERT_NEAR(0.022750131948179216, libgp::cdf_norm(-2.00), err);
  ASSERT_NEAR(0.040059156863817079, libgp::cdf_norm(-1.75), err);
  ASSERT_NEAR(0.066807201268858085, libgp::cdf_norm(-1.50), err);
  ASSERT_NEAR(0.105649773666855282, libgp::cdf_norm(-1.25), err);
  ASSERT_NEAR(0.158655253931457046, libgp::cdf_norm(-1.00), err);
  ASSERT_NEAR(0.226627352376868207, libgp::cdf_norm(-0.75), err);
  ASSERT_NEAR(0.308537538725986937, libgp::cdf_norm(-0.50), err);
  ASSERT_NEAR(0.401293674317076299, libgp::cdf_norm(-0.25), err);
  ASSERT_NEAR(0.500000000000000000, libgp::cdf_norm(0.00), err);
  ASSERT_NEAR(0.598706325682923701, libgp::cdf_norm(0.25), err);
  ASSERT_NEAR(0.691462461274013007, libgp::cdf_norm(0.50), err);
  ASSERT_NEAR(0.773372647623131737, libgp::cdf_norm(0.75), err);
  ASSERT_NEAR(0.841344746068542926, libgp::cdf_norm(1.00), err);
  ASSERT_NEAR(0.894350226333144760, libgp::cdf_norm(1.25), err);
  ASSERT_NEAR(0.933192798731141915, libgp::cdf_norm(1.50), err);
  ASSERT_NEAR(0.959940843136182886, libgp::cdf_norm(1.75), err);
  ASSERT_NEAR(0.977249868051820791, libgp::cdf_norm(2.00), err);
  ASSERT_NEAR(0.987775527344955329, libgp::cdf_norm(2.25), err);
  ASSERT_NEAR(0.993790334674223841, libgp::cdf_norm(2.50), err);
  ASSERT_NEAR(0.997020236764945444, libgp::cdf_norm(2.75), err);
  ASSERT_NEAR(0.998650101968369897, libgp::cdf_norm(3.00), err);
  ASSERT_NEAR(0.999422974957609234, libgp::cdf_norm(3.25), err);
  ASSERT_NEAR(0.999767370920964460, libgp::cdf_norm(3.50), err);
  ASSERT_NEAR(0.999911582714799185, libgp::cdf_norm(3.75), err);
  ASSERT_NEAR(0.999968328758166880, libgp::cdf_norm(4.00), err);
  ASSERT_NEAR(0.999989311474225095, libgp::cdf_norm(4.25), err);
  ASSERT_NEAR(0.999996602326875261, libgp::cdf_norm(4.50), err);
  ASSERT_NEAR(0.999998982916757484, libgp::cdf_norm(4.75), err);
  ASSERT_NEAR(0.999999713348428076, libgp::cdf_norm(5.00), err);
  ASSERT_NEAR(0.999999923950394831, libgp::cdf_norm(5.25), err);
  ASSERT_NEAR(0.999999981010437522, libgp::cdf_norm(5.50), err);
  ASSERT_NEAR(0.999999995537827591, libgp::cdf_norm(5.75), err);
  ASSERT_NEAR(0.999999999013412300, libgp::cdf_norm(6.00), err);
  ASSERT_NEAR(0.999999999794773609, libgp::cdf_norm(6.25), err);
  ASSERT_NEAR(0.999999999959840014, libgp::cdf_norm(6.50), err);
  ASSERT_NEAR(0.999999999992607691, libgp::cdf_norm(6.75), err);
  ASSERT_NEAR(0.999999999998720135, libgp::cdf_norm(7.00), err);
  ASSERT_NEAR(0.999999999999791611, libgp::cdf_norm(7.25), err);
  ASSERT_NEAR(0.999999999999968137, libgp::cdf_norm(7.50), err);
  ASSERT_NEAR(0.999999999999995448, libgp::cdf_norm(7.75), err);
  ASSERT_NEAR(0.999999999999999334, libgp::cdf_norm(8.00), err);
}
