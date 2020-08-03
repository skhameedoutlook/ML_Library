#include <iostream>
#include <string>
#include <DataSet.cpp>
#include <vector>

class LinearRegressionModel {
private:
	vector<string> features;
	vector<string> labels;
	vector<long double> errors;
	long double x_bar;
	long double y_bar;
	long double x_sd;
	long double y_sd;
	long double correlation;
	long double mss;
	long double train_percent;
	long double test_percent;
public:
	LinearRegressionModel(DataSet* ds, string feature, string label, map<string, unsigned long long>& indices) {
		for(unsigned long long i = 0; i < (*ds).getNumRows(); i++) {
			features.push_back((*(*(*(*(*ds).getRows())[i]).getRow())[indices[feature]]).getValue());
			labels.push_back((*(*(*(*(*ds).getRows())[i]).getRow())[indices[label]]).getValue());
		}
	}
};