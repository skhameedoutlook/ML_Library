#include <iostream>
#include <string>
#include <Field.cpp>
#include <Row.cpp>
#include <vector>

using namespace std;

class DataSet {
private:
	unsigned long long numRows;
	unsigned long long numFields;
	vector<string*> names;
	vector<string*> sizes;
	vector<string*> types;
	vector<Row*> rows;
public:
	DataSet(vector<string>& pnames, vector<string>& ptypes, vector<string>& psizes, vector<vector<string> >& pdata) {
		numRows = pdata.size();
		numFields = pnames.size();
		for(unsigned long long i = 0; i < numFields; i++) {
			names.push_back(&pnames[i]);
			sizes.push_back(&psizes[i]);
			types.push_back(&ptypes[i]);
		}
		for(unsigned long long i = 0; i < numRows; i++) {
			rows.push_back(new Row(pnames, ptypes, psizes, pdata[i]));
		}
	}
	void displayData(string seperator) {
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
};