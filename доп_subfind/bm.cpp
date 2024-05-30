#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>


int NaiveSearch(const std::string& str, const std::string& sub)
{
    size_t n = str.size(), m = sub.size(), j = 0;
    for (size_t i = 0; i <= n - m; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (str[i + j] != sub[j])
                break;
        }
        if (j == m)
            return i;
    }
    return -1;
}

void ComputeKmpTable(const std::string& sub, int* lps)
{
    int j = 0;
    lps[0] = 0;
    for (size_t i = 1; i < sub.size(); i++)
    {
        while (j > 0 && sub[i] != sub[j])
            j = lps[j - 1];
        if (sub[i] == sub[j])
            j++;
        lps[i] = j;
    }
}

int KmpSearch(const std::string& str, const std::string& sub)
{
    size_t m = sub.size();
    int* lps = new int[m];
    ComputeKmpTable(sub, lps);

    int j = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        while (j > 0 && str[i] != sub[j])
            j = lps[j - 1];
        if (str[i] == sub[j])
        {
            j++;
            if (j == m)
            {
                delete[] lps;
                return i - j + 1;
            }
        }
    }
    delete[] lps;
    return -1;
}

int BmSearch(const std::string& str, const std::string& sub)
{
    int last[256];
    std::fill(last, last + 256, -1);
    for (size_t i = 0; i < sub.size(); i++)
        last[(unsigned char)sub[i]] = i;

    int s = 0;
    while (s <= static_cast<int>(str.size() - sub.size()))
    {
        int j = sub.size() - 1;
        while (j >= 0 && sub[j] == str[s + j])
            j--;
        if (j < 0)
            return s;
        else
            s += std::max(1, j - last[(unsigned char)str[s + j]]);
    }
    return -1;
}

int main()
{
    using namespace std;
    string path = "engwiki_ascii.txt";
    string sub = "was born in a small town called Sceptre";
    string str;

    ifstream fin(path, ios::binary);
    if (!fin.is_open())
    {
        cout << "File could not be read" << endl;
        return 0;
    }
    str.assign((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    const size_t n = 10;
    long long times[n];
    int indx[n];

    chrono::high_resolution_clock::time_point start, end;

    cout << "\nNaive Search\n";
    for (size_t i = 0; i < n; i++)
    {
        start = chrono::high_resolution_clock::now();
        int index = NaiveSearch(str, sub);
        end = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        indx[i] = index;
        cout << indx[i] << '\t' << times[i] << " ms" << endl;
    }

    cout << "\nKMP Search\n";
    for (size_t i = 0; i < n; i++)
    {
        start = chrono::high_resolution_clock::now();
        int index = KmpSearch(str, sub);
        end = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        indx[i] = index;
        cout << indx[i] << '\t' << times[i] << " ms" << endl;
    }

    cout << "\nBM Search\n";
    for (size_t i = 0; i < n; i++)
    {
        start = chrono::high_resolution_clock::now();
        int index = BmSearch(str, sub);
        end = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        indx[i] = index;
        cout << indx[i] << '\t' << times[i] << " ms" << endl;
    }

    return 0;
}
