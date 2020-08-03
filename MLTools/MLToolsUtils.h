#include<string>
#include <vector>
#include <sstream>

using namespace std;

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