// Örn Óli Strange
// 21.09.18

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

typedef unsigned int uint;

int tempIp[4];

string dottedIp(int *ip) {
    string out;
    for (int i = 0; i < 3; i++)
        out += to_string(ip[i]) + ".";
    out += ip[3];
    return out;
};

string ipPadded(int *ip) {
    string out;
    int strLen;
    out += dottedIp(ip);
    strLen = out.length();
    for (int i = 0; i < 16 - strLen; i++)
        out += " ";
    out += "|";
    return out;
};

string maskPadded(uint mask) {
    string out = "255.255.255.";
    int strLen;
    out += to_string(mask);
    strLen = out.length();
    for (int i = 0; i < 16 - strLen; i++)
        out += " ";
    out += "|";
    return out;
};

int * firstUsable(int *ip) {
    copy(ip, ip+4, tempIp);
    tempIp[3] += 1;
    return tempIp;
};

int * lastUsable(int *ip, int magicNum) {
    copy(ip, ip+4, tempIp);
    tempIp[3] += magicNum - 2;
    return tempIp;
};

int * broadCast(int *ip, int magicNum) {
    copy(ip, ip+4, tempIp);
    tempIp[3] += magicNum - 1;
    return tempIp;
};

void printIp(int *ip, uint mask, int magicNum) {
    cout << ipPadded(ip)
         << ipPadded(firstUsable(ip))
         << ipPadded(lastUsable(ip, magicNum))
         << ipPadded(broadCast(ip, magicNum))
         << maskPadded(mask)
         << endl;
};

int * setIpNetwork(int *ip, int network) {
    copy(ip, ip+4, tempIp);
    tempIp[3] = network;
    return tempIp;
};

int main() {
    int ip[4], bits, div, bitsReq, lastOne, magicNumber;
    uint netMask;
    string dashLine = "----------------+";

    cout << "Sláðu inn upphafsnet: ";
    for (int i = 0; i < 4; i++)
        cin >> ip[i];
    
    cout << "Sláðu inn fjölda netbita í upphafsneti: ";
    cin >> bits;

    cout << "Sláðu inn fjölda neta sem skipta á upphafsnetinu í: ";
    cin >> div;

    cout << endl
         << "Ip net          |" << "Fyrsta Nothæfa  |"
         << "Síðasta nothæfa |" << "Broadcast       |"
         << "Maski           |"  << endl;
    cout << dashLine << dashLine << dashLine << dashLine << dashLine << endl;

    bitsReq = log2(div);
    lastOne = 32 - (bits + bitsReq);
    magicNumber = pow(2, lastOne);
    netMask = 0xffffffff << (32 - (bits + bitsReq));

    for (int i = 0; i < div; i++) {
        printIp(setIpNetwork(ip, i * magicNumber), netMask, magicNumber);
    };

    return 0;
};
