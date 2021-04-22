// Sweep Parameter base code

//doesn't actually use all these libraries, so I'll cut them down later
#include <iostream>
#include <iomanip>
#include <vector> 
#include <valarray>
#include <map>
#include <string>
#include <utility>
#include <regex>
#include <functional>
#include <sstream>
#include <iterator>
#include <utility>
#include <tuple>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <numeric>
#include <ctype.h>
#include "json/value.h"
#include "json/json.h"
#include <boost/thread.hpp>
#include <queue>

using namespace std;
using namespace boost::filesystem;

//Note: some indexing and variable need to be renamed to accomodate our json fields, but I can do that later once
//all the inputs are finalized

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

vector<double> range(double min, double max, size_t N) {
    vector<double> range;
    double delta = (max-min)/double(N-1);
    for(int i=0; i<N; i++) {
        range.push_back(min + i*delta);
    }
    return range;
}

vector<vector<double>> cartesian( vector<vector<double> >& v ) {
  vector<vector<double>> results;
  auto product = []( long long a, vector<double>& b ) { return a*b.size(); };
  const long long N = accumulate( v.begin(), v.end(), 1LL, product );
  vector<double> u(v.size());
  for( long long n=0 ; n<N ; ++n ) {
    lldiv_t q { n, 0 };
    for( long long i=v.size()-1 ; 0<=i ; --i ) {
      q = div( q.quot, v[i].size() );
      u[i] = v[i][q.rem];
    }

    
      results.push_back(u);
  }
  return results;
}

bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
 
    return true;
}

int main() {

    //loads rocket json as object and assigns it to Json::Value rocket. 
    std::string rocketJSONPath = "Input_File.json";
    std::ifstream rocketStream(rocketJSONPath);
    Json::Value rocket;
    rocketStream >> rocket;

	vector<vector<double>> params;
    vector<vector<double>> array;
    vector<double> values{0,0,0};

    int num = rocket["sweep"].size();

    for (int i = 0; i < num; i++) {
        for (int j = 0; j<3; j++){
            double value = rocket["sweep"][i]["value"][j].asDouble();
            values[j] = value;
        }
        array.push_back(values);
    }

    // creates arrays of the parameters 
    for (int i = 0; i < num; i++) {
        double min = array[i][0];
        double max = array[i][1];
        int N = array[i][2];
        auto paramX = range(min, max, N);
        params.push_back(paramX);
    }
    // computes the cartesian product of the
    auto parametersFull = cartesian(params);

    vector<vector<string>> parameterNames;
    for (int i = 0; i < num; i++) {
        std::string s = rocket["sweep"][i]["field"].asString();
        std::string delimiter = ".";
        auto parameterX = split(s, delimiter);
        parameterNames.push_back(parameterX);
    }

    //puts cartesian product values back into the json and prints updated object values to validate
    for (int i = 0; i<parametersFull.size(); i++){
        for (int j=0; j<parametersFull[0].size(); j++){
            Json::Value* current = &rocket;
                for (std::string param : parameterNames[j]) {
                    if (isNumber(param)) {
                        int number = stoi(param);
          				current = &(*current)[number];
                        continue;
                    }
                current = &(*current)[param];
                }
            *current = parametersFull[i][j];
        }

        //**PROGRAM GOES HERE**
    }

}




