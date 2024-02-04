// next[j] means: when 0~j-1 match but j doesn't, then j = next[j];
// next[j] also means: pattern[0:j-1] has next[j] length of longest prefix and suffix
//                                                   (pattern[0:next[j]-1]  ==  pattern[j-next[j]:j-1])
// i       = 01234567 
// pattern = abcabca
// next_j = -10001234
void init_next(const string& pattern, vector<int>& next)
{
    int j = -1;
    next.resize(pattern.size()+1);
    next[0] = -1;
    int i = 0;
    for (int i = 0; i < pattern.size(); ++i) {
        while (j != -1 && pattern[i] != pattern[j]) j = next[j];
        next[i+1] = ++j;
    }
}

int KMP_search(const string& s, const string& pattern, int& ii, int& jj, vector<int>& next)
{
    int j = jj;
    for (int i = ii; i < s.size(); ++i) {
        while (j != -1 && s[i] != pattern[j]) j = next[j];
        j++;
        if (j == pattern.size()) {
            ii = i+1;
            jj = next[j];
            return ii - j;
        }
    }
    ii = 0;
    jj = 0;
    return -1; 
}

class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> ret;
        int n = s.size();
        vector<int> nexta;
        init_next(a, nexta);
        vector<int> nextb;
        init_next(b, nextb);

        vector<int> pre_sum = vector<int>(n, 0);
        int ii = 0, jj = 0;
        int y = 0;
        while (true) {
            int start = KMP_search(s, b, ii, jj, nextb);
            if (start == -1) {
                for (;y < n; ++y) {
                    if (y == n) {
                        pre_sum[y] = ((y==0)?0:pre_sum[y-1]) + 1;
                    } else {
                        pre_sum[y] = ((y==0)?0:pre_sum[y-1]);
                    }
                }
                break;
            }
            for (;y <= start; ++y) {
                if (y == start) {
                    pre_sum[y] = ((y==0)?0:pre_sum[y-1]) + 1;
                } else {
                    pre_sum[y] = ((y==0)?0:pre_sum[y-1]);
                }
            }
        }
        while (true) {
            int start = KMP_search(s, a, ii, jj, nexta);
            if (start == -1) {
                break;
            }
            int i = start;
            if (((i+k >= n)?pre_sum[n-1]:pre_sum[i+k]) != ((i-k-1 < 0)?0:pre_sum[i-k-1])) ret.push_back(i);
        }
        return ret;
    }
};
