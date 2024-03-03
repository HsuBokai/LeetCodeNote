int M = 1e9+7;
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
        memset(arr, 0, sizeof(arr));
        memset(lazy, 0, sizeof(lazy));
        int n2 = 1;
        while (n2 < n) {
            n2 *= 2;
        }
        arr[0+n2] = 1;
        for (int i = n2-1; i > 0; --i) {
            arr[i] = arr[i*2] + arr[i*2+1];
        }
        long long ret = 0;
        long long add = 0;
        add = 1;
        ret = (ret + add) % M;
        for (int i = 1; i < n; ++i) {
            // get sum from [la[i]+1 : i]
            //cout << la[i]+1 << ':' << i << endl;
            long long s = get(1, 0, n2-1, la[i]+1, i);
            /*
            long long s = 0;
            for (int j = i; j > la[i]; --j) {
                s = (s + arr[j+n2]) % M;
            }
            */
            //cout << s << endl;
            // update [la[i]+1 : i]  increment 1
            update(1, 0, n2-1, la[i]+1, i);
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
};