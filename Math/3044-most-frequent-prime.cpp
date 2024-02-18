
class Solution {
    char is_prime[1000005];
    // Try to make max_n as small as possible to prevent TLE
    void init_is_prime(int max_n) {
        memset(is_prime, 0xFF, sizeof(is_prime));
        is_prime[0] = 0;
        is_prime[1] = 0;
        for (int x = 2; x <= sqrt(max_n); x++) {
            if (is_prime[x] != 0) {
                for (int y = x*x; y <= max_n; y+=x) is_prime[y] = 0;
            }
        }
    }
public:
    int mostFrequentPrime(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int nnn = max(n,m);
        int large = 1;
        for (int i = 0; i < nnn; ++i) large *= 10;
        init_is_prime(large);
        unordered_map<int,int> obj;
        int mx_freq = 0;
        vector<pair<int,int>> dir = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (auto& p : dir) {
                    int ii = i;
                    int jj = j;
                    int x = mat[i][j];
                    while (true) {
                        ii += p.first;
                        jj += p.second;
                        if (0 <= ii && ii < n && 0 <= jj && jj < m) {
                            x *= 10;
                            x += mat[ii][jj];
                            if (is_prime[x] != 0) {
                                if (obj.find(x) == obj.end()) {
                                    obj[x] = 1;
                                } else {
                                    obj[x]++;
                                }
                                mx_freq = max(mx_freq, obj[x]);
                            }
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        int ret = -1;
        for (auto& p : obj) {
            if (p.second == mx_freq) ret = max(ret, p.first);
        }
        return ret;
        
    }
};