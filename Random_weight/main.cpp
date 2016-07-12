#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct PairKeyWeight {
    PairKeyWeight() : key(0), weight(0)
    {
    };
    unsigned int key;
    unsigned int weight;
};

unsigned int GetRand(int min, int max)
{
    if (min > max)
        swap(min, max);
    int inter_val = max - min + 1;

    return rand() % inter_val + min;
}

vector<string> split(const string &str, const char c)
{
    vector<string> res;
    unsigned int pos = 0;

    string temp_str = str;
    string strstr;
    while((pos = temp_str.find(c)) != str.npos)
    {
        strstr = temp_str.substr(0, pos);
        temp_str.erase(0, pos + 1);
        //cout << strstr << endl;
        //cout << temp_str << endl;
        res.push_back(strstr);
    }
    res.push_back(temp_str);

    return res;
}

void replace_char(string &str, const char c, const char rep_c)
{
    unsigned int beg = 0;
    unsigned int pos = 0;

    while ((pos = str.find(c, beg)) != str.npos)
    {
        str[pos] = rep_c;
        beg = pos;
    }

}

int main() {

    vector<PairKeyWeight> test_vec;
    PairKeyWeight one;

    ifstream in_f("t.txt");
//#define in_f cin

    srand(time(NULL));
    if(in_f)
    {
        string in_str;
        while (in_f >> in_str)
        {
            if(!in_str.empty())
            {
                auto at_vals = split(in_str, ';');
                if (at_vals.size() >= 2)
                {
                    one.key = atoi(at_vals[0].c_str());
                    one.weight = atoi(at_vals[1].c_str());
                    test_vec.push_back(one);
                    cout << "key : " << one.key << endl;
                    cout << "weight : " << one.weight << endl;
                }
            }
        }
    }

    unsigned int total_weight = 0;
    for(unsigned int x = 0; x < test_vec.size(); ++x)
    {
        total_weight += test_vec[x].weight;
    }

    unsigned int inter_ran_val = GetRand(0, (int)total_weight - 1);
    unsigned int inter_sum = 0;
    unsigned int r_index = 0;
    for(unsigned int x = 0; x < test_vec.size() - 1; ++x)
    {
        inter_sum += test_vec[x].weight;
        if(inter_ran_val < inter_sum)
        {
            r_index = x;
            break;
        }
    }

    cout << "index : " << r_index << endl;
    cout << test_vec[r_index].key << endl;

    string str_c_s = "abc;efg;oog;;";
    replace_char(str_c_s, ';', ' ');
    cout << str_c_s << endl;

    return 0;
}