#include <iostream>
#include <string>
#include <DataSet.cpp>
#include <vector>
#include <sstream>

long double calcMeanFromString(vector<string> array) {
	long double sum = 0;
	long double item;
	string strItem;
	for(unsigned long long i = 0; i < array.size(); i++) {
		stringstream strItem(array[i]);
		strItem >> item;
		sum += item;
	}
	return sum/array.size();
}

long double calcSDFromString(vector<string> array, long double mean) {
	long double sum = 0;
	long double item;
	string strItem;
	for(unsigned long long i = 0; i < array.size(); i++) {
		stringstream strItem(array[i]);
		strItem >> item;
		sum += (mean-item)*(mean-item);
	}
	return sqrt(sum/array.size());
}

long double calcCorrelationFromString(vector<string> x, vector<string> y, long double x_bar, long double y_bar, long double x_sd, long double y_sd) {
	long double sum = 0;
	long double item1, item2;
	string strItem;
	for(unsigned long long i = 0; i < x.size(); i++) {
		stringstream strItem(x[i]);
		strItem >> item1;
		for(unsigned long long i = 0; i < y.size(); i++) {
			stringstream strItem(y[i]);
			strItem >> item2;
			sum += (item1-x_bar)*(item2-y_bar);
		}
	}
	sum /= (x_sd*y_sd);
	return sum/(x.size()-1);
}

long double stringToLongDouble(string s) {
	long double item;
	stringstream strItem(s);
	strItem >> item;
	return item;
}

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
	long double trainRows;
public:
	LinearRegressionModel(DataSet* ds, string feature, string label, map<string, unsigned long long>& indices, long double train) {
		train_percent = train;
		trainRows = (train/100)*((*ds).getNumRows());
		for(unsigned long long i = 0; i < (*ds).getNumRows(); i++) {
			features.push_back((*(*(*(*(*ds).getRows())[i]).getRow())[indices[feature]]).getValue());
			labels.push_back((*(*(*(*(*ds).getRows())[i]).getRow())[indices[label]]).getValue());
		}
	}
	void train() {
		x_bar = calcMeanFromString(features);
		y_bar = calcMeanFromString(labels);
		x_sd = calcSDFromString(features, x_bar);
		y_sd = calcSDFromString(labels, y_bar);
		correlation = calcCorrelationFromString(features, labels, x_bar, y_bar, x_sd, y_sd);
		slope = correlation*(y_sd/x_sd);
		intercept = y_bar - (slope*x_bar);
	}
	void predict() {
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
	long double calcMSS() {
		long double sum = 0;
		for(unsigned long long i = 0; i < errors.size(); i++) {
			sum += (errors[i]*errors[i]);
		}
		return sum/errors.size();
	}
	long double getMSS() {
		predict();
		return mss;
	}
	long double displayPrediction() {
		predict();
		cout << "Original\t\t\t\tPredicted" << endl;
		for(unsigned long long i = trainRows; i < features.size(); i++) {
			cout << stringToLongDouble(features[i]) << "\t\t\t\t" << predicted[i] << endl;
		}
	}
};