#include <iostream>
#include "largeClass/largeClass.h"
#include "stdlib.h"
#include "time.h"
#include <string>
#include <fstream>
#define TOO_LARGE_MSG 1

using namespace std;

void readKeys(largeClass &a, largeClass &b, string filename)
{
    ifstream ifst(filename.c_str());
    string a_str, b_str;
    getline(ifst, a_str);
    getline(ifst, b_str);

    a = largeClass(a_str.c_str());
    b = largeClass(b_str.c_str());
}

largeClass encrypt(largeClass m, largeClass e, largeClass n)
{
	if (m >= n)
	{
		throw TOO_LARGE_MSG;
	}
    return powModClass(m, e, n);
}

largeClass decrypt(largeClass c, largeClass d, largeClass n)
{
    return powModClass(c, d, n);
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        cerr << "Usage: rsa <key_name> <infile> <outfile> {e,d}" << endl;
        return 1;
    }
    string key_name = argv[1];
    string infile = argv[2];
    string outfile = argv[3];
    string flag = argv[4];

    if (flag == "e")
    {
        largeClass e, n;
        readKeys(e, n, key_name + ".pub");
        largeClass m;
        m.readFromBinFile(infile.c_str());
        largeClass c;
        try
        {
        	c = encrypt(m, e, n);
        }
        catch (int err)
        {
        	if (err == TOO_LARGE_MSG)
        	{
        		cerr << "Too large message. Choose longer key" << endl;
        		return 1;
        	}
        }

        c.writeToTextFile(outfile.c_str());
    }
    else
    {
        largeClass d, n;
        readKeys(d, n, key_name + ".priv");
        largeClass c;
        c.readFromTextFile(infile.c_str());
        largeClass m = decrypt(c, d, n);

        m.writeToBinFile(outfile.c_str());
    }
    return 0;
}
