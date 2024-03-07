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
};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        int mx = 0;
        for (auto& v : nums) mx = max(mx, v);
        mx++;
        SegTree *rootA = new SegTree(1, mx);
        SegTree *rootB = new SegTree(1, mx);
        rootA->update(nums[0],nums[0]);
        rootB->update(nums[1],nums[1]);
        vector<int> arr1(1, nums[0]);
        vector<int> arr2(1, nums[1]);
        for (int i = 2; i < nums.size(); ++i) {
            int v = nums[i];
            int sa = rootA->query(v+1, mx);
            int sb = rootB->query(v+1, mx);
            //cout << sa << ',' << sb << endl;
            if (sa > sb) {
                arr1.push_back(v);
                rootA->update(v,v);
            } else if (sa < sb) {
                arr2.push_back(v);
                rootB->update(v,v);
            } else {
                if (arr1.size() <= arr2.size()) {
                    arr1.push_back(v);
                    rootA->update(v,v);
                } else {
                    arr2.push_back(v);
                    rootB->update(v,v);
                }
            }
        }
        for (auto& v : arr2) arr1.push_back(v);
        return arr1;
    }
};
