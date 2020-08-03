#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <DataSet.h>
#include <LinearRegressionModel.h>

using namespace std;

void fillOccurences(string line, string seperator, vector<unsigned long long>& occurences) {
	unsigned long long count = 0;
	for(unsigned long long i = 0; i < line.length()-seperator.length(); i++) {
		if(line.substr(i, 1).compare(seperator) == 0) {
			occurences.push_back(i);
		}
	}
}

vector<string> tokenize(string line, string seperator) {
	vector<string> result;
	vector<unsigned long long> occurences;
	fillOccurences(line, seperator, occurences);
	unsigned long long previous = -1;
	for(unsigned long long i = 0; i < occurences.size(); i++) {
		string field = "";
		for(unsigned long long j = previous+1; j < occurences[i]; j++) {
			field += line[j];
		}
		result.push_back(field);
		previous = occurences[i];
	}
	string field = "";
	for(unsigned long long i = previous+1; i < line.size(); i++) {
		field += line[i];
	}
	if(!(field.compare("") == 0)) {
		result.push_back(field);
	}
	return result;
}

vector<string> strSplit(string line, string seperator) {
	vector<string> result;
	for(unsigned long long i = 0; i < 5; i++) {
		result.push_back("Test");
	}
	return result;
}

int main() {
	fstream file("test_input2.txt");
	vector<string> rowData;
	vector<vector<string> > fullData;
	string line, seperator = " ";
	vector<string> names, sizes, types;
	getline(file, line);
	names = tokenize(line, seperator);
	getline(file, line);
	types = tokenize(line, seperator);
	getline(file, line);
	sizes = tokenize(line, seperator);
	while(getline(file, line)) {
		rowData = tokenize(line, seperator);
		fullData.push_back(rowData);
	}
	file.close();
	DataSet* ds;
	ds = new DataSet(names, types, sizes, fullData, 0);
	ds->displayData(", ");
	LinearRegressionModel* model = new LinearRegressionModel(ds, "col1", "col2", *(ds->getFieldIndices()), 50);
	model->train();
	model->displayPrediction();

	return  0;
}