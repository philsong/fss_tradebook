#include "contract.hpp"

#include <iostream>
#include <cstdio>
#include <memory>


/*
Based on response at:
http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c/479103
*/
string exec_result(string command) {
    // Create pipe file pointer with deleter pclose
    shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        cerr << "Unable to open pipe for command: " << command;
    }

    char buffer[128];
    string result = "";
    while(!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }

    return result;
}

Contract::Contract(string s, string n, string e, double p) :
    symbol {s}, name {n}, exchange {e}, lastPrice {p} { }

void Contract::request_info(string quandl_code) {
    cout << "Requesting using curl: \n";
        //  << exec_result("curl -L http://www.quandl.com/api/v3/datasets/MGEX/MWH2012.csv") << '\n';

    // Read in result csv file

    // 2nd Line field index 4 has last Price

    // Exchange and symbol from quandl code

    // Name from lookup in symbols? maybe pass all this stuff along?

    // Construct contract object
}

string Contract::toString() {
    return
    "Name: " + name + '\n' +
    "Symbol: " + symbol + '\n' +
    "Exchange: " + exchange + '\n' +
    "Last Price: " + to_string(lastPrice) + '\n';
}

string Contract::get_name() {
    return name;
}

double Contract::get_last_price() {
    return lastPrice;
}
