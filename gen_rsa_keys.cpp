#include <iostream>
#include "largeClass/largeClass.h"
#include "stdlib.h"
#include "time.h"
#include <string>
#include <fstream>

using namespace std;

// x = 1/a mod b на основе расширенного алгоритма Евклида
largeClass inv(largeClass a, largeClass b)
{
    largeClass m = b;
    largeClass x1 = (long long) 0;
    largeClass x2 = 1;
    largeClass y1 = 1;
    largeClass y2 = (long long) 0;
    largeClass x, y;

    while (b != (long long) 0)
    {
        largeClass q = a / b;
        largeClass r = a % b;
        a = b;
        b = r;
        largeClass xx = x2 - x1 * q;
        largeClass yy = y2 - y1 * q;
        x2 = x1;
        x1 = xx;
        y2 = y1;
        y1 = yy;
        x = x2;
        y = y2;
    }
    return (x + m) % m;
}

void gen_rsa_keys(int bitlen, string key_name)
{
    // Выбираются два различных случайных простых числа p и q заданного размера (например, 1024 бита каждое).
    largeClass p = GenPrime(bitlen);
    largeClass q = GenPrime(bitlen);
    while (p == q)
        q = GenPrime(bitlen);

    // Вычисляется их произведение n=p*q, которое называется модулем.
    largeClass n = p * q;

    // Вычисляется значение функции Эйлера от числа n
    largeClass phi = (p - 1) * (q - 1);

    // Выбирается целое число e
    largeClass e = 65537;

    // Вычисляется число d, мультипликативно обратное к числу e по модулю phi(n)
    largeClass d = inv(e, phi);

    ofstream pub((key_name + string(".pub")).c_str());
    ofstream priv((key_name + string(".priv")).c_str());

    pub << e.str() << endl << n.str() << endl;
    priv << d.str() << endl << n.str() << endl;
}

int main(int argc, char* argv[])
{
    srand(time(0));
    if (argc != 3)
    {
        cerr << "Generate keys for RSA" << endl;
        cerr << "Usage: gen_rsa_keys <bitlen> <key_name>" << endl;
        return 1;
    }
    gen_rsa_keys(atoi(argv[1]), argv[2]);
    return 0;
}
