/*
z[j] : 0 ~ pattern.size()-1
z[j] means: pattern[0:z[j]-1]  ==  pattern[j:j+z[j]-1])

i       = 0123456 
pattern = abcabca
z_j     = 7004001

i       = 0123456 
pattern = aaaaaaa
z_j     = 7654321

i       = 0123456 
pattern = aabaacd
z_j     = 7102100

i       = 0123456 
pattern = abababab
z_j     = 80604020

*/

void init_z(const string& pattern, vector<int>& z)
{
    int n = pattern.size();
    z.resize(n);
    int l = 0, r = 0;
    z[0] = n;
    for (int i = 1; i < n; i++) {
        if (i < r) {
            z[i]=min(r-i, z[i-l]);
        }
        while (i+z[i] < n && pattern[z[i]] == pattern[i+z[i]]) {
            z[i]++;
        }
        if (i+z[i] > r) {
            l=i;
            r=i+z[i];
        }
    }
}

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
        vector<int> z;
        init_z(word, z);
        int ret = 0;
        for (int i = k; i < n; i+=k) {
            //cout << z[i] << endl;
            if (z[i] == (n-i)) {
                return ret+1;
            }
            ret++;
        }
        return ret+1;
    }
    int minimumTimeToInitialState_use_2_hash(string word, int k) {
        int n = word.size();
        vector<unsigned long long> h1_arr;
        unsigned long long h1 = 0;
        vector<unsigned long long> h2_arr;
        unsigned long long h2 = 0;
        for (int i = (n-1); i >= 0; --i) {
            h1 *= 26;
            h1 += (word[i]-'a');
            h1_arr.push_back(h1);
            h2 *= 31;
            h2 += (word[i]-'a');
            h2_arr.push_back(h2);
        }
        reverse(h1_arr.begin(), h1_arr.end());
        reverse(h2_arr.begin(), h2_arr.end());
        vector<unsigned long long> rh1_arr;
        unsigned long long base1 = 1;
        unsigned long long rh1 = 0;
        vector<unsigned long long> rh2_arr;
        unsigned long long base2 = 1;
        unsigned long long rh2 = 0;
        for (int i = 0; i < n; ++i) {
            rh1 += (base1 * (word[i]-'a'));
            base1 *= 26;
            rh1_arr.push_back(rh1);
            rh2 += (base2 * (word[i]-'a'));
            base2 *= 31;
            rh2_arr.push_back(rh2);
        }
        int ret = 0;
        for (int start = k; start < n; start += k) {
            if (h1_arr[start] == rh1_arr[n-1-start] && h2_arr[start] == rh2_arr[n-1-start]) {
                int the_same = 1;
                for (int xx = start, yy = 0; xx < n; ++xx, ++yy) {
                    if (word[xx] != word[yy]) {
                        the_same = 0;
                        break;
                    }
                }
                if (the_same == 1) {
                    return ret+1;
                }   
            }
            ret++;
        }
        return ret+1;
    }
};