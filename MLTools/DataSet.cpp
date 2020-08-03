#include <iostream>
#include <string>
#include <Field.cpp>
#include <Row.cpp>
#include <vector>
#include <map>
#include <DataSet.h>

using namespace std;



DataSet::DataSet(vector<string>& pnames, vector<string>& ptypes, vector<string>& psizes, vector<vector<string> >& pdata, long double train) {
	train_percent = train;
	numRows = pdata.size();
	numFields = pnames.size();
	for(unsigned long long i = 0; i < numFields; i++) {
		names.push_back(&pnames[i]);
		field_indices[pnames[i]] = i;
		sizes.push_back(&psizes[i]);
		types.push_back(&ptypes[i]);
	}
	for(unsigned long long i = 0; i < numRows; i++) {
		rows.push_back(new Row(pnames, ptypes, psizes, pdata[i]));
	}
}
void DataSet::displayData(string seperator) {
	for(unsigned long long i = 0; i < rows.size(); i++) {
		vector<Field*>* currentRow = rows[i]->getRow();
		for(unsigned long long i = 0; i < (*currentRow).size(); i++) {
			if(i == (*currentRow).size()-1) {
				cout << (*(*currentRow)[i]).getValue();
			}
			else {
				cout << (*(*currentRow)[i]).getValue() << seperator;
			}
		}
		cout << endl;
	}
}
vector<Row*>* DataSet::getRows() {
	return &rows;
}
unsigned long long DataSet::getNumRows() {
	return numRows;
}
unsigned long long DataSet::getNumFields() {
	return numFields;
}
map<string, unsigned long long>* DataSet::getFieldIndices() {
	return &field_indices;
}