#include <string>
#include <Field.cpp>
#include <vector>

using namespace std;

class Row {
private:
	vector<string> names;
	vector<Field*> fields;
	vector<Field*> subFields;
public:
	Row(vector<string>& pnames, vector<string>& ptypes, vector<string>& psizes, vector<string>& pvalues) {
		for(unsigned long long i = 0; i < pnames.size(); i++) {
			fields.push_back(new Field(pnames[i], ptypes[i], psizes[i], pvalues[i]));
		}
	}
	vector<Field*>* getRow()  {
		return &fields;
	}
	vector<Field*>* getSubRow(vector<unsigned long long>& indexes) {
		subFields.clear();
		for(unsigned long long i = 0; i < indexes.size(); i++) {
			subFields.push_back(fields[indexes[i]]);
		}
		return &subFields;
	}
};