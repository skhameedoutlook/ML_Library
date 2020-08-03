#include <string>
#pragma once

using namespace std;

class Field {
private:
	string name;
	string type;
	string size;
	string value;
public:
	Field(string pname, string ptype, string psize, string val) {
		name = pname;
		type = ptype;
		size = psize;
		value = val;
	}
	string getName() {
		return name;
	}
	string getValue() {
		return value;
	}
	string getSize() {
		return size;
	}
	string getType() {
		return type;
	}
};