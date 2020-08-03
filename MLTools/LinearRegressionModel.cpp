#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <LinearRegressionModel.h>
#include <MLToolsUtils.h>


LinearRegressionModel::LinearRegressionModel(DataSet* ds, string feature, string label, map<string, unsigned long long>& indices, long double train) {
	train_percent = train;
	trainRows = floor((train/100)*((*ds).getNumRows()));
	for(unsigned long long i = 0; i < (*ds).getNumRows(); i++) {
		features.push_back((*(*(*(*(*ds).getRows())[i]).getRow())[indices[feature]]).getValue());
		labels.push_back((*(*(*(*(*ds).getRows())[i]).getRow())[indices[label]]).getValue());
	}
}
void LinearRegressionModel::train() {
	x_bar = calcMeanFromString(features);
	y_bar = calcMeanFromString(labels);
	x_sd = calcSDFromString(features, x_bar);
	y_sd = calcSDFromString(labels, y_bar);
	correlation = calcCorrelationFromString(features, labels, x_bar, y_bar, x_sd, y_sd);
	slope = correlation*(y_sd/x_sd);
	intercept = y_bar - (slope*x_bar);
	cout << "x_bar: " << x_bar << endl;
	cout << "y_bar: " << y_bar << endl;
	cout << "x_sd: " << x_sd << endl;
	cout << "y_sd: " << y_sd << endl;
	cout << "r: " << correlation << endl;
	cout << "slope: " << slope << endl;
	cout << "intercept: " << intercept << endl;
}
void LinearRegressionModel::predict() {
	predicted.clear();
	errors.clear();
	long double predictedValue;
	for(unsigned long long i = trainRows; i < features.size(); i++) {
		predictedValue = (slope*stringToLongDouble(features[i])) + intercept;
		predicted.push_back(predictedValue);
		errors.push_back(predictedValue-stringToLongDouble(labels[i]));
	}
	mss = calcMSS();
}
long double LinearRegressionModel::calcMSS() {
	long double sum = 0;
	for(unsigned long long i = 0; i < errors.size(); i++) {
		sum += (errors[i]*errors[i]);
	}
	return sum/errors.size();
}
long double LinearRegressionModel::getMSS() {
	predict();
	return mss;
}
void LinearRegressionModel::displayPrediction() {
	predict();
	cout << "Original\t\t\t\tPredicted" << endl;
	unsigned long long j = 0;
	for(unsigned long long i = trainRows; i < features.size(); i++, j++) {
		cout << stringToLongDouble(features[i]) << "\t\t\t\t" << predicted[j] << endl;
	}
}
