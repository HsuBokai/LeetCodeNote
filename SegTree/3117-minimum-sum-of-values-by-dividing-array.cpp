
class SegTree1 {
public:
    int n2;
    vector<int> segtree;

    void min_init(int n) {
        n2 = 1;
        while (n2 < n) {
            n2 *= 2;
        }
        segtree = vector<int>(n2*2, INT_MAX);
    }

    void min_clear() {
        for (int i = 0; i < segtree.size(); ++i)
            segtree[i] = INT_MAX;
    }

    void min_update_1(int i , int l, int r, int index, int value) {
        if (l == r) {
            segtree[i] = min(segtree[i], value);
            return;
        }
        int mid = l + (r-l)/2;
        segtree[i] = min(segtree[i], value);
        if (index <= mid) min_update_1(2*i, l, mid, index, value);
        else min_update_1(2*i+1, mid+1, r, index, value);
    }
    void min_update(int index, int value) {
        return min_update_1(1, 0, n2-1, index, value);
    }

    int min_query_1(int i, int l, int r, int range_l, int range_r) {
        //cout << l << ':' << r << ':' << range_l << ':' << range_r << endl;
        if (l == range_l && r == range_r) {
            return segtree[i];
        }
        int mid = l + (r-l)/2;
        if (range_r <= mid) return min_query_1(2*i, l, mid, range_l, range_r);
        if (range_l > mid) return min_query_1(2*i+1, mid+1, r, range_l, range_r);
        int a = min_query_1(2*i, l, mid, range_l, mid);
        int b = min_query_1(2*i+1, mid+1, r, mid+1, range_r);
        return min(a, b);
    }
    int min_query(int range_l, int range_r) {
        return min_query_1(1, 0, n2-1, range_l, range_r);
    }
};


class Solution {
public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        int n = nums.size();
        int m = andValues.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        vector<vector<int>> arr(n, vector<int>(20, -1));
        for (int j = 0; j < 20; ++j) {
            int ans = -1;
            for (int i = 0; i < n; ++i) {
                if (nums[i] & (1<<j)) {
                    arr[i][j] = ans;
                } else {
                    ans = i;
                    arr[i][j] = ans;
                }
            }
        }
        SegTree1 minobj;
        minobj.min_init(n);
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                if (j == 0) {
                    vector<pair<int,int>> obj;
                    for (int x = 0; x < 20; ++x) {
                        obj.push_back({arr[i][x], x});
                    }
                    sort(obj.rbegin(), obj.rend());
                    int v = nums[i];
                    int find_x = -1;
                    for (int x = 0; x < 20; ++x) {
                        if (obj[x].first >= 0) {
                            v = v & (~(1<<(obj[x].second)));
                            if (v == andValues[j]) {
                                find_x = x;
                            }
                        }
                    }
                    if (find_x != -1) {
                        dp[i][j] = nums[i];
                    }
                } else {
                    vector<pair<int,int>> obj;
                    for (int x = 0; x < 20; ++x) {
                        obj.push_back({arr[i][x], x});
                    }
                    sort(obj.rbegin(), obj.rend());
                    int v = nums[i];
                    int find_x = -1;
                    for (int x = 0; x < 20; ++x) {
                        if (obj[x].first >= 0) {
                            v = v & (~(1<<(obj[x].second)));
                            if (v == andValues[j]) {
                                find_x = x;
                            }
                        }
                    }
                    if (find_x != -1) {
                        int end = obj[find_x].first - 1;
                        int start = ((find_x == 19) ? 0 : (obj[find_x+1].first));
                        if (start == -1) start = 0;
                        if (start <= end) {
                            //cout << start << ',' << end << '=' << endl;
                            int prev = minobj.min_query(start, end);
                            //cout << prev << endl;
                            if (prev != INT_MAX) {
                                // get min value in [start, end]
                                dp[i][j] = prev + nums[i];
                            }
                        }
                    }
                }
            }
            minobj.min_clear();
            for (int i = 0; i < n; ++i) {
                if (dp[i][j] != -1) {
                    //cout << i << ':' << dp[i][j] << endl;
                    minobj.min_update(i, dp[i][j]);
                }
            }
        }
        return dp[n-1][m-1];
        
    }
};