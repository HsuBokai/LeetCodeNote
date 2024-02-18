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

// get all length with the same prefix and suffix of pattern
// pattern = abcabca
// len = {7, 4, 1}
void init_prefix_suffix_len(const string& pattern, vector<int>& next, vector<int>& len)
{
    int l = pattern.size();
    do {
        len.push_back(l);
        l = next[l];
    } while (l > 0);
}

#define MAX_CH 26
class TrieNode {
public:
    TrieNode* child[MAX_CH];
    vector<int> many_index;
    TrieNode () {
        memset(child, 0, sizeof(child));
    }
};

class Solution {
    vector<vector<int>> arr;
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        long long ret = 0;
        int n = words.size();
        arr = vector<vector<int>>(n);
        for (int i = 0; i < n; ++i) {
            init_next(words[i], arr[i]);
        }
        TrieNode root;
        for (int i = 0; i < n; ++i) {
            int l = words[i].size();
            vector<int> all_len;
            init_prefix_suffix_len(words[i], arr[i], all_len);
            unordered_set<int> obj(all_len.begin(), all_len.end());
            TrieNode* tmp = &root;
            for (int j = 0; j < l; ++j) {
                int v = words[i][j]-'a';
                if (tmp->child[v] == NULL) {
                    tmp->child[v] = new TrieNode();
                }
                tmp = tmp->child[v];
                if (tmp->many_index.size() > 0) {
                    int iii = tmp->many_index[0];
                    int lll = words[iii].size();
                    if (obj.find(lll) != obj.end()) ret += tmp->many_index.size();
                }
            }
            tmp->many_index.push_back(i);
        }
        return ret;
        
    }
};