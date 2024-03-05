int M = 1e9+7;

class SegTree {
public:
    SegTree *left;
    SegTree *right;
    long long l;
    long long r;
    long long value;
    long long lazy;
    SegTree(long long a, long long b, long long v) {
        left = NULL;
        right = NULL;
        l = a;
        r = b;
        value = v;
        lazy = 0;
    }
    
    // update value+1 of [a:b]
    void update(long long a, long long b) {
        if (l == a && r == b) {
            if (l == r) {
                value = (value + 1) % M;
            } else {
                lazy = (lazy + 1) % M;
            }
            return;
        }
        //cout << l << 'x' << r << endl;
        long long mid = l + (r-l)/2;
        if (left == NULL || right == NULL) {
            left = new SegTree(l, mid, value);
            left->lazy = lazy;
            right = new SegTree(mid+1, r, value);
            right->lazy = lazy;
        }
        value = (value + (b - a + 1)) % M;
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
            return (value + x) % M;
        }
        long long mid = l + (r-l)/2;
        if (left == NULL || right == NULL) {
            return value;
        } else {
            if (lazy > 0) {
                left->lazy = (left->lazy + lazy) % M;
                right->lazy = (right->lazy + lazy) % M;
                long long x = (r-l+1);
                x *= lazy;
                value = (value + x) % M;
                lazy = 0;
            }
            if (b <= mid) return left->query(a,b);
            if (a > mid) return right->query(a,b);
            long long ret = 0;
            ret = (ret + left->query(a,mid)) % M;
            ret = (ret + right->query(mid+1,b)) % M;
            return ret;
        }
    }
};

class Solution {
    vector<int> la;
    long long lazy[270004];
    long long arr[270004];
public:
    long long get(int i, int is, int ie, int start, int end) {
        int mid = is + (ie - is) / 2;
        if (start == is && end == ie) {
            long long x = (ie-is+1);
            x *= lazy[i];
            return (arr[i] + x) % M;
        }
        if (lazy[i] > 0) {
            lazy[2*i] = (lazy[2*i] + lazy[i]) % M;
            lazy[2*i+1] = (lazy[2*i+1] + lazy[i]) % M;
            long long x = (ie-is+1);
            x *= lazy[i];
            arr[i] = (arr[i] + x) % M;
            lazy[i] = 0;
        }
        if (end <= mid) return get(2*i, is, mid, start, end);
        if (mid < start) return get(2*i+1, mid+1, ie, start, end);
        long long ret = 0;
        ret += get(2*i, is, mid, start, mid);
        ret += get(2*i+1, mid+1, ie, mid+1, end);
        return ret;
    }
    void update(int i, int is, int ie, int start, int end) {
        int mid = is + (ie - is) / 2;
        if (start == is && end == ie) {
            lazy[i] = (lazy[i] + 1) % M;
            return;
        }
        arr[i] = (arr[i] + (end - start + 1)) % M;
        if (end <= mid) return update(2*i, is, mid, start, end);
        if (mid < start) return update(2*i+1, mid+1, ie, start, end);
        update(2*i, is, mid, start, mid);
        update(2*i+1, mid+1, ie, mid+1, end);
    }
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        la = vector<int>(n);
        unordered_map<int,int> m2;
        for (int i = 0; i < n; ++i) {
            if (m2.find(nums[i]) == m2.end()) {
                la[i] = -1;
            } else {
                la[i] = m2[nums[i]];
            }
            m2[nums[i]] = i;
        }
        /*memset(arr, 0, sizeof(arr));
        memset(lazy, 0, sizeof(lazy));
        int n2 = 1;
        while (n2 < n) {
            n2 *= 2;
        }
        arr[0+n2] = 1;
        for (int i = n2-1; i > 0; --i) {
            arr[i] = arr[i*2] + arr[i*2+1];
        }*/
        SegTree *root = new SegTree(0, n+1, 0);
        root->update(0, 0);
        long long ret = 0;
        long long add = 0;
        add = 1;
        ret = (ret + add) % M;
        for (int i = 1; i < n; ++i) {
            // get sum from [la[i]+1 : i]
            //cout << la[i]+1 << ':' << i << endl;
            //long long s = get(1, 0, n2-1, la[i]+1, i);
            long long s = root->query(la[i]+1, i);
            /*
            long long s = 0;
            for (int j = i; j > la[i]; --j) {
                s = (s + arr[j+n2]) % M;
            }
            */
            //cout << s << endl;
            // update [la[i]+1 : i]  increment 1
            //update(1, 0, n2-1, la[i]+1, i);
            root->update(la[i]+1, i);
            /*
            for (int j = i; j > la[i]; --j) {
                arr[j+n2]++;
            }
            */
            add = (add + s) % M;
            add = (add + s) % M;
            add = (add + (i-la[i])) % M;
            ret = (ret + add) % M;
        }
        return ret;
    }
    /*
    int sumCounts_way2(vector<int>& nums) {
        int n = nums.size();
        ra = vector<int>(n);
        la = vector<int>(n);
        unordered_map<int,int> m;
        for (int i = n-1; i >= 0; --i) {
            if (m.find(nums[i]) == m.end()) {
                ra[i] = n;
            } else {
                ra[i] = m[nums[i]];
            }
            m[nums[i]] = i;
        }
        unordered_map<int,int> m2;
        for (int i = 0; i < n; ++i) {
            if (m2.find(nums[i]) == m2.end()) {
                la[i] = -1;
            } else {
                la[i] = m2[nums[i]];
            }
            m2[nums[i]] = i;
        }
        return helper(nums, 0, n-1);
    }
    
    long long helper(vector<int>& nums, int start, int end) {
        if (start == end) {
            return 1;
        }
        long long ans = 0;
        int mid = start + (end - start) / 2;
        ans = (ans + helper(nums, start, mid)) % M;
        ans = (ans + helper(nums, mid+1, end)) % M;
        int a = 0;
        for (int i = mid+1; i <= end; ++i) {
            if (la[i] < (mid+1)) {
                a++;
            }
            arr[i] = a;
        }
        long long add = 0;
        int i = mid;
            for (int j = mid+1; j <= end; ++j) {
                if (j < ra[i]) {
                    arr[j] += 1;
                }
                long long b = arr[j];
                b = (b * arr[j]) % M;
                add = (add + b) % M;
            }
        ans = (ans + add) % M;
        for (int i = mid-1; i >= start; --i) {
            long long bb = 0;
            for (int j = mid+1; j <= end; ++j) {
                if (j < ra[i]) {
                    bb = (bb + arr[j]) % M;
                    bb = (bb + arr[j]) % M;
                    bb = (bb + 1) % M;
                    arr[j] += 1;
                } else {
                    break;
                }
            }
            add = (add + bb);
            ans = (ans + add) % M;
        }
        return ans;
    }
    */
};
