#include <iostream>
#include <string>
#include <time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>

#include <fstream>
using namespace std;

#define Random(x) (rand() % x) //通过取余取得指定范围的随机数
string removeZero(string x) {
    //去除字符串前多余的0
    int len = x.size();
    if (len <= 1)return x;
    int i = 0;
    while (x[i] == '0')i++;
    if (i == len)return "0";
    return x.substr(i, len - i + 1);

}
string buZero(string a, int num) {
    if (num <= 0)return a;
    //给字符串补0,相当于10进制的a左移num位
    a = removeZero(a);
    string res(num, '0');
    return a + res;
}
string add(string a, string b) {
    //实现字符串的加法
    a = removeZero(a);
    b = removeZero(b);
    if (a == "0" && b == "0")return "0";
    int lenA = a.size();
    int lenB = b.size();
    if (b == "")return a;
    if (a == "")return b;
    string MaxStr = lenA > lenB ? a : b;
    string MinStr = lenA > lenB ? b : a;
    int MaxLen = lenA > lenB ? lenA : lenB;
    int MinLen = lenA > lenB ? lenB : lenA;
    string  res; res.resize(MaxLen + 1);

    int jin = 0, sum = 0;
    int i = MaxLen - 1;
    int j = MinLen - 1;
    for (; j >= 0; j--) {
        sum = (MaxStr[i] - '0') + MinStr[j] - '0' + jin;
        res[i + 1] = sum % 10 + '0';
        jin = sum / 10;
        i--;
    }
    for (; i >= 0; i--) {
        sum = (MaxStr[i] - '0') + jin;
        res[i + 1] = sum % 10 + '0';
        jin = sum / 10;
    }
    if (jin != 0) {
        res[0] = jin + '0';
    }
    else {
        res = res.substr(1, MaxLen + 1);
    }

    return removeZero(res);
}
string jian(string a, string b) {
    //字符串计算a-b
    a = removeZero(a);
    b = removeZero(b);
    if (a == "0" && b == "0")return 0;
    int lenA = a.size();
    int lenB = b.size();
    //cout<<"jian   a: "<<a<< " b: " <<b<<"\n"<<endl;
    string MaxStr = lenA >= lenB ? a : b;
    string MinStr = lenA >= lenB ? b : a;
    int MaxLen = lenA >= lenB ? lenA : lenB;
    int MinLen = lenA >= lenB ? lenB : lenA;
    string  res; res.resize(MaxLen);

    int i = MinLen - 1;
    int j = MaxLen - 1;
    int sum = 0;
    for (; i >= 0; i--) {

        int c = MaxStr[j] - '0';
        int cc = MinStr[i] - '0';
        if (c < cc) {
            for (int jie = j - 1; jie >= 0; jie--) {
                if (MaxStr[jie] >= '1') {
                    MaxStr[jie] = MaxStr[jie] - 1;
                    break;
                }
                else {
                    MaxStr[jie] = '9';
                }
            }
            sum = c + 10 - cc;
            res[j] = sum + '0';
        }
        else {
            res[j] = c - cc + '0';
        }
        j--;
    }
    for (; j >= 0; j--) {
        res[j] = MaxStr[j];
    }

    res = removeZero(res);//去除多余的前导0

    return res;
}
string chen(string a, char b) {
    //字符串a*b ，这里的b只有1位
    a = removeZero(a);

    if (b == '0')return "0";
    if (b == '1')return a;
    int len = a.size();
    int sum = 0, jin = 0;
    int bb = b - '0';
    for (int i = len - 1; i >= 0; i--) {
        sum = (a[i] - '0') * bb + jin;
        a[i] = sum % 10 + '0';
        jin = sum / 10;
    }
    string res = "";
    if (jin > 0) {
        char c = jin + '0';
        res = c + a;
    }
    else {
        res = a;
    }

    return res;

}

string baseBigInteger(string a, string b) {
    //模拟十进制的整数乘法
    a = removeZero(a);
    b = removeZero(b);
    int lenA = a.size();
    int lenB = b.size();
    cout << "jian   a: " << a << " b: " << b << "\n" << endl;
    string MaxStr = lenA >= lenB ? a : b;
    string MinStr = lenA >= lenB ? b : a;
    int MaxLen = lenA >= lenB ? lenA : lenB;
    int MinLen = lenA >= lenB ? lenB : lenA;

    string res = "";
    int bu = 0;
    for (int j = MinLen - 1; j >= 0; j--) {

        string t = buZero(chen(MaxStr, MinStr[j]), bu);
        res = add(t, res);
        bu++;
    }
    return removeZero(res);
}
string getRandomStr(long num) {
    srand((int)time(NULL));
    string res(num, '0');
    int x;
    while ((x = Random(10)) == 0);
    res[0] = x + '0';
    for (long i = 1; i < num; i++) {
        res[i] = Random(10) + '0';
    }
    return res;
}
string baseFenZhi(string a, string b) {
    a = removeZero(a);
    b = removeZero(b);
    int lenA = a.size();
    int lenB = b.size();
    //cout<<"jian   a: "<<a<< " b: " <<b<<"\n"<<endl;
    string MaxStr = lenA >= lenB ? a : b;
    string MinStr = lenA >= lenB ? b : a;
    int MaxLen = lenA >= lenB ? lenA : lenB;
    int MinLen = lenA >= lenB ? lenB : lenA;

    if (MinLen == 0)return "0";
    if (MinLen == 1)return chen(MaxStr, MinStr[0]);
    int m1 = MaxLen / 2, m2 = MaxLen - m1;
    int n1 = MinLen / 2, n2 = MinLen - n1;

    string A = MaxStr.substr(0, m1);
    string B = MaxStr.substr(m1, m2);
    string C = MinStr.substr(0, n1);
    string D = MinStr.substr(n1, n2);

    string AC = buZero(baseFenZhi(A, C), m2 + n2);
    string AD = buZero(baseFenZhi(A, D), m2);
    string BC = buZero(baseFenZhi(B, C), n2);
    string BD = baseFenZhi(B, D);

    string t1 = add(AC, AD);
    string t2 = add(BC, BD);
    return add(t1, t2);
}
string fenZhiPro(string a, string b) {
    a = removeZero(a);
    b = removeZero(b);
    int lenA = a.size();
    int lenB = b.size();
    //cout<<"jian   a: "<<a<< " b: " <<b<<"\n"<<endl;
    string MaxStr = lenA >= lenB ? a : b;
    string MinStr = lenA >= lenB ? b : a;
    int MaxLen = lenA >= lenB ? lenA : lenB;
    int MinLen = lenA >= lenB ? lenB : lenA;
    if (MinLen == 1)return chen(MaxStr, MinStr[0]);

    int n1 = MinLen / 2, n2 = MinLen - n1;
    int m1 = MaxLen - n2, m2 = n2;



    string A = MaxStr.substr(0, m1);
    string B = MaxStr.substr(m1, m2);
    string C = MinStr.substr(0, n1);
    string D = MinStr.substr(n1, n2);

    string AC = fenZhiPro(A, C);
    string BD = fenZhiPro(B, D);

    string A_B = jian(A, B);
    string D_C = jian(D, C);
    string t = fenZhiPro(A_B, D_C);
    string t1 = add(AC, BD);
    string t2 = buZero(add(t, t1), m2);

    string acT = buZero(AC, 2 * m2);

    string tt = add(acT, t2);

    return add(tt, BD);

}
void once(long length, string path, string(*func)(string a, string b), string funcName) {
    string a = getRandomStr(length);
    string b = getRandomStr(length);
    //cout<<"a: "<<a<<" b:"<<b<<endl;
    ofstream outfile(path, ios::app);
    struct timeval sTime, eTime;
    gettimeofday(&sTime, NULL);
    string res = func(a, b);
    gettimeofday(&eTime, NULL);
    long exeTime = (eTime.tv_sec - sTime.tv_sec) * 1000000 + (eTime.tv_usec - sTime.tv_usec);
    outfile << funcName << " length" << length << " time: " << exeTime * pow(10, -6) << " s" << endl;
    outfile.close();
}

int main() {

    long wei = 10;
    long all = 10000000000;
    while (wei <= all) {
        cout << "fenZhiPro wei: " << wei << endl;
        once(wei, "../fenZhiPro_1.txt", fenZhiPro, "fenZhiPro");
        wei *= 10;
    }

    wei = 10;
    while (wei <= all) {
        cout << "baseFenZhi wei: " << wei << endl;
        once(wei, "../baseFenZhi_1.txt", baseFenZhi, "baseFenZhi");
        wei *= 10;
    }

    wei = 10;
    while (wei <= all) {
        cout << " baseBigInteger wei: " << wei << endl;
        once(wei, "../baseFenZhi_1.txt", baseBigInteger, "baseBigInteger");
        wei *= 10;
    }

    return 0;

}