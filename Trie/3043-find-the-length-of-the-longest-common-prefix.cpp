#define MAX_CH 26
class TrieNode {
public:
    TrieNode* child[MAX_CH];
    TrieNode () {
        memset(child, 0, sizeof(child));
    }
};

class Solution {
public:
    
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        int ret = 0;
        TrieNode root;
        for (auto& v : arr1) {
            vector<int> arr;
            while (v > 0) {
                arr.push_back(v%10);
                v /= 10;
            }
            TrieNode* tmp = &root;
            for (int i = arr.size()-1; i >= 0; --i) {
                int x = arr[i];
                if (tmp->child[x] == NULL) {
                    tmp->child[x] = new TrieNode();
                }
                tmp = tmp->child[x];
            }
        }
        for (auto& v : arr2) {
            int r = 0;
            vector<int> arr;
            while (v > 0) {
                arr.push_back(v%10);
                v /= 10;
            }
            TrieNode* tmp = &root;
            for (int i = arr.size()-1; i >= 0; --i) {
                int x = arr[i];
                if (tmp->child[x] == NULL) {
                    break;
                } else {
                    tmp = tmp->child[x];
                    r = max(r, (int)(arr.size()-i));
                }
            }
            ret = max(ret, r);
        }
        return ret;
    }
    int get_len(int v) {
        int l = 10;
        for (int i = 0; i < 9; ++i) {
            if (v < l) return i+1;
            l *= 10;
        }
        return 10;
    }
    int longestCommonPrefix2(vector<int>& arr1, vector<int>& arr2) {
        vector<int> pow10;
        int v = 1;
        for (int i = 0; i < 9; ++i) {
            pow10.push_back(v);
            v *= 10;
        }
        for (int ret = 9; ret > 0; ret--) {
            unordered_map<int,int> mm;
            for (auto& v : arr1) {
                int l = get_len(v);
                if (l >= ret) {
                    int x = v / pow10[l-ret];
                    if (mm.find(x) == mm.end()) {
                        mm[x] = 1;
                    }
                }
            }
            for (auto& v : arr2) {
                int l = get_len(v);
                if (l >= ret) {
                    int x = v / pow10[l-ret];
                    if (mm.find(x) != mm.end()) {
                        return ret;
                    }
                }
            }
        }
        return 0;
    }
};