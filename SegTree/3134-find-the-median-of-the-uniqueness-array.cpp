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



class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> prev(n, -1);
        unordered_map<int,int> obj;
        for (int i = 0; i < n; ++i) {
            if (obj.find(nums[i]) == obj.end()) {
                prev[i] = -1;
            } else {
                prev[i] = obj[nums[i]];
            }
            obj[nums[i]] = i;
        }

        int l = 1;
        int r = set(nums.begin(), nums.end()).size();
        long long limit = n;
        limit *= (n+1);
        limit /= 2;
        limit += 1;
        limit /= 2;
        SegTree1 seg;
        seg.sum_init(n);
        while (l < r) {
            int mid = l + (r-l)/2;
            long long count = 0;
            seg.sum_clear();
            int ind = -1;
            for (int i = 0; i < n; ++i) {
                //cout << prev[i]+1 << ',' << i << endl;
                seg.sum_update_range(prev[i]+1, i, 1);
                while (ind < i && seg.sum_query_lazy(ind+1, ind+1) > mid) ind++;
                count += (i-ind);
                if (count >= limit) break;
            }
            if (count >= limit) {
                r = mid;
            } else {
                l = mid+1;
            }
        }
        return r;
    }
};