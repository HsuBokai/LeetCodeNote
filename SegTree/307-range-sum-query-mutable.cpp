class SegTree1 {
public:
    int n2;
    vector<int> segtree;

    // sum op

    void sum_init(int n) {
        n2 = 1;
        while (n2 < n) {
            n2 *= 2;
        }
        segtree = vector<int>(n2*2, 0);
    }

    void sum_init(vector<int>& nums) {
        int n = nums.size();
        n2 = 1;
        while (n2 < n) {
            n2 *= 2;
        }
        segtree = vector<int>(n2*2, 0);
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
        for (int i = 0; i < segtree.size(); ++i)
            segtree[i] = 0;
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

    int sum_query_1(int i, int l, int r, int range_l, int range_r) {
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
    int sum_query(int range_l, int range_r) {
        return sum_query_1(1, 0, n2-1, range_l, range_r);
    }

    // min op

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



class NumArray {
    SegTree1 obj;
public:
    NumArray(vector<int>& nums) {
        obj.sum_init(nums);
    }
    
    void update(int index, int val) {
        obj.sum_update(index, val);
    }
    
    int sumRange(int left, int right) {
        return obj.sum_query(left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */