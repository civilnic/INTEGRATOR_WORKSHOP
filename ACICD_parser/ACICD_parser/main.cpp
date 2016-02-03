#include <iostream>
#include <string>
#include <fstream>

#include "csv.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    io::CSVReader<28,io::trim_chars<' '>, io::no_quote_escape<'\t'>, io::single_line_comment<'#'>>  in("acicd.csv");
    int a;
    while(in.read_row(a)){
        cout << "a" + a << endl;

      }
    return 0;
}

