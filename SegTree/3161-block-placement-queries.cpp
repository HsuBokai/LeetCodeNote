long long segtree[262144];
long long lazy[262144];

class SegTree1 {
public:
    int n2;

    /*vector<long long> segtree;
    vector<long long> lazy;*/

    // sum op

    void sum_init(int n) {
        n2 = 1;
        while (n2 < n) {
            n2 *= 2;
        }
        //segtree = vector<long long>(n2*2, 0);
        //lazy = vector<long long>(n2*2, 0);
    }

    void sum_init(vector<int>& nums) {
        int n = nums.size();
        n2 = 1;
        while (n2 < n) {
            n2 *= 2;
        }
        //segtree = vector<long long>(n2*2, 0);
        //lazy = vector<long long>(n2*2, 0);
        for (int i = 0; i < n; ++i) {
            segtree[n2+i] = nums[i];
        }
        for (int i = n2-1; i >= 1; --i) {
            int left = 2*i;
            int right = left + 1;
            segtree[i] = segtree[left] + segtree[right];
        }
    }

    void sum_clear() {
        memset(segtree, 0, sizeof(segtree));
        memset(lazy, 0, sizeof(lazy));
        /*for (int i = 0; i < segtree.size(); ++i) {
            segtree[i] = 0;
            lazy[i] = 0;
        }*/
    }

    // update +value of [a:b]
    void sum_update_range_1(int i , int l, int r, int a, int b, int value) {
        if (l == a && r == b) {
            if (l == r) {
                segtree[i] = (segtree[i] + value);
            } else {
                lazy[i] = (lazy[i] + value);
            }
            return;
        }
        //cout << l << 'x' << r << endl;
        long long mid = l + (r-l)/2;
        segtree[i] = (segtree[i] + ((b-a+1)*value) + ((r-l+1)*lazy[i]));
        lazy[2*i] += lazy[i];
        lazy[2*i+1] += lazy[i];
        lazy[i] = 0;
        if (b <= mid) {
            sum_update_range_1(2*i, l, mid, a, b, value);
        } else if (a > mid) {
            sum_update_range_1(2*i+1, mid+1, r, a, b, value);
        } else {
            sum_update_range_1(2*i, l, mid, a, mid, value);
            sum_update_range_1(2*i+1, mid+1, r, mid+1, b, value);
        }
        
    }
    void sum_update_range(int a, int b, int value) {
        return sum_update_range_1(1, 0, n2-1, a, b, value);
    }

    void sum_update_1(int i , int l, int r, int index, int value) {
        if (l == r) {
            segtree[i] += (value - segtree[n2+index]);
            return;
        }
        int mid = l + (r-l)/2;
        segtree[i] += (value - segtree[n2+index]);
        if (index <= mid) sum_update_1(2*i, l, mid, index, value);
        else sum_update_1(2*i+1, mid+1, r, index, value);
    }
    void sum_update(int index, int value) {
        return sum_update_1(1, 0, n2-1, index, value);
    }

    long long sum_query_1(int i, int l, int r, int range_l, int range_r) {
        //cout << l << ':' << r << ':' << range_l << ':' << range_r << endl;
        if (l == range_l && r == range_r) {
            return segtree[i];
        }
        int mid = l + (r-l)/2;
        if (range_r <= mid) return sum_query_1(2*i, l, mid, range_l, range_r);
        if (range_l > mid) return sum_query_1(2*i+1, mid+1, r, range_l, range_r);
        int a = sum_query_1(2*i, l, mid, range_l, mid);
        int b = sum_query_1(2*i+1, mid+1, r, mid+1, range_r);
        return a + b;
    }
    long long sum_query(int range_l, int range_r) {
        return sum_query_1(1, 0, n2-1, range_l, range_r);
    }

    long long sum_query_lazy_1(int i, int l, int r, int range_l, int range_r) {
        //cout << l << ':' << r << ':' << range_l << ':' << range_r << endl;
        if (l == range_l && r == range_r) {
            int x = (r-l+1);
            x *= lazy[i];
            return (segtree[i] + x);
        }
        int mid = l + (r-l)/2;
        if (lazy[i] > 0) {
            lazy[2*i] += lazy[i];
            lazy[2*i+1] += lazy[i];
            long long x = (r-l+1);
            x *= lazy[i];
            segtree[i] = (segtree[i] + x);
            lazy[i] = 0;
        }
        if (range_r <= mid) return sum_query_lazy_1(2*i, l, mid, range_l, range_r);
        if (range_l > mid) return sum_query_lazy_1(2*i+1, mid+1, r, range_l, range_r);
        int a = sum_query_lazy_1(2*i, l, mid, range_l, mid);
        int b = sum_query_lazy_1(2*i+1, mid+1, r, mid+1, range_r);
        return a + b;
    }
    long long sum_query_lazy(int range_l, int range_r) {
        return sum_query_lazy_1(1, 0, n2-1, range_l, range_r);
    }

    // min op

    void min_init(int n) {
        n2 = 1;
        while (n2 < n) {
            n2 *= 2;
        }
        //segtree = vector<long long>(n2*2, INT_MAX);
    }

    void min_clear() {
        //for (int i = 0; i < segtree.size(); ++i)
        //    segtree[i] = INT_MAX;
    }

    void min_update_1(int i , int l, int r, int index, long long value) {
        if (l == r) {
            segtree[i] = min(segtree[i], value);
            return;
        }
        int mid = l + (r-l)/2;
        segtree[i] = min(segtree[i], value);
        if (index <= mid) min_update_1(2*i, l, mid, index, value);
        else min_update_1(2*i+1, mid+1, r, index, value);
    }
    void min_update(int index, long long value) {
        return min_update_1(1, 0, n2-1, index, value);
    }

    long long min_query_1(int i, int l, int r, int range_l, int range_r) {
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
    long long min_query(int range_l, int range_r) {
        return min_query_1(1, 0, n2-1, range_l, range_r);
    }
};

class SegTree {
public:
    SegTree *left;
    SegTree *right;
    long long l;
    long long r;
    long long value;
    long long lazy;
    SegTree(long long a, long long b) {
        left = NULL;
        right = NULL;
        l = a;
        r = b;
        value = 0;
        lazy = 0;
    }
    
    // update value+1 of [a:b]
    void update(long long a, long long b) {
        if (l == a && r == b) {
            if (l == r) {
                value = (value + 1);
            } else {
                lazy = (lazy + 1);
            }
            return;
        }
        //cout << l << 'x' << r << endl;
        long long mid = l + (r-l)/2;
        if (left == NULL || right == NULL) {
            left = new SegTree(l, mid);
            left->lazy = lazy;
            right = new SegTree(mid+1, r);
            right->lazy = lazy;
        }
        value = (value + (b - a + 1));
        if (b <= mid) return left->update(a, b);
        if (a > mid) return right->update(a, b);
        left->update(a, mid);
        right->update(mid+1, b);
    }
    
    // query sum value of [a:b]
    long long query(long long a, long long b) {
        if (l == a && r == b) {
            long long x = (r-l+1);
            x *= lazy;
            return (value + x);
        }
        long long mid = l + (r-l)/2;
        if (left == NULL || right == NULL) {
            return 0;
        } else {
            if (lazy > 0) {
                left->lazy = (left->lazy + lazy);
                right->lazy = (right->lazy + lazy);
                long long x = (r-l+1);
                x *= lazy;
                value = (value + x);
                lazy = 0;
            }
            if (b <= mid) return left->query(a,b);
            if (a > mid) return right->query(a,b);
            long long ret = 0;
            ret = (ret + left->query(a,mid));
            ret = (ret + right->query(mid+1,b));
            return ret;
        }
    }

    // change value = y at x
    void max_update(long long x, long long y) {
        if (l == x && r == x) {
            value = y;
            return;
        }
        //cout << l << 'x' << r << endl;
        long long mid = l + (r-l)/2;
        if (left == NULL || right == NULL) {
            left = new SegTree(l, mid);
            left->lazy = lazy;
            right = new SegTree(mid+1, r);
            right->lazy = lazy;
        }
        if (x <= mid) left->max_update(x, y);
        else right->max_update(x, y);
        value = max(left->value, right->value);
    }
    
    // query max value of [a:b]
    long long max_query(long long a, long long b) {
        if (l == a && r == b) {
            return (value);
        }
        long long mid = l + (r-l)/2;
        if (left == NULL || right == NULL) {
            return 0;
        } else {
            if (b <= mid) return left->max_query(a,b);
            if (a > mid) return right->max_query(a,b);
            long long ret = 0;
            ret = max(ret, left->max_query(a,mid));
            ret = max(ret, right->max_query(mid+1,b));
            return ret;
        }
    }
};


class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        vector<bool> ret;
        SegTree *tree = new SegTree(0, 50005);
        map<int,int> pre_len;
        for (auto& q : queries) {
            int x = q[1];
            if (q[0] == 1) {
                auto it = pre_len.upper_bound(x);
                int value;
                if (it != pre_len.begin()) {
                    value = x - prev(it)->first;
                } else {
                    value = x;
                }
                pre_len[x] = value;
                tree->max_update(x, value);
                //cout << x << ':' << value << endl;
                int mn;
                if (it != pre_len.end()) {
                    int next_x = it->first;
                    int new_x = next_x - x;
                    pre_len[next_x] = new_x;
                    tree->max_update(next_x, new_x);
                }
            } else {
                int mx = tree->max_query(0, x);
                auto it = pre_len.upper_bound(x);
                if (it != pre_len.begin()) {
                    it = prev(it);
                    mx = max(mx, x - (it->first));
                } else {
                    mx = max(mx, x);
                }
                if (q[2] <= mx) {
                    ret.push_back(true);
                } else {
                    ret.push_back(false);
                }
            }
        }
        return ret;
    }
};