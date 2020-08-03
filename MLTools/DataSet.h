#include <iostream>
#include <string>
#include <Field.cpp>
#include <Row.cpp>
#include <vector>
#include <map>
#pragma once

using namespace std;

class DataSet {
private:
	unsigned long long numRows;
	unsigned long long numFields;
	vector<string*> names;
	vector<string*> sizes;
	vector<string*> types;
	vector<Row*> rows;
	map<string, unsigned long long> field_indices;
	long double train_percent;
public:
	DataSet(vector<string>&, vector<string>&, vector<string>&, vector<vector<string> >&, long double);
	void displayData(string);
	vector<Row*>* getRows();
	unsigned long long getNumRows();
	unsigned long long getNumFields();
	map<string, unsigned long long>* getFieldIndices();
};