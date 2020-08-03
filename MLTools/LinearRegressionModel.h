#include <iostream>
#include <string>
#include <DataSet.h>
#include <vector>
#include <sstream>
#pragma once

class LinearRegressionModel {
private:
	vector<string> features;
	vector<string> labels;
	vector<long double> predicted;
	vector<long double> errors;
	long double x_bar;
	long double y_bar;
	long double x_sd;
	long double y_sd;
	long double correlation;
	long double mss;
	long double train_percent;
	long double slope;
	long double intercept;
	unsigned long long trainRows;
public:
	LinearRegressionModel(DataSet*, string, string, map<string, unsigned long long>&, long double);
	void train();
	void predict();
	long double calcMSS();
	long double getMSS();
	void displayPrediction();
};