// Lazy Propagation -> Optimised code for updating the value in the given range and get the sum in given range

#include<bits/stdc++.h>
using namespace std;

class SEGTree{
    public:
    vector<int> seg, lazy;
    SEGTree(int n){
        seg.resize(4*n);
        lazy.resize(4*n);
    }
    
    void build(int indx, int low, int high, vector<int> &arr){
        if(low == high){
            seg[indx] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        
        build(2 * indx + 1, low, mid, arr);
        build(2 * indx + 2, mid + 1, high, arr);
        seg[indx] = seg[2 * indx + 1] + seg[2 * indx + 2];
    }
    
    void update(int indx, int low, int high, int l, int r, int val){
        if(lazy[indx] != 0){
            int node = (high - low + 1);
            seg[indx] += (node * lazy[indx]);
            if(low != high){
                lazy[2 * indx + 1] += lazy[indx];
                lazy[2 * indx + 2] += lazy[indx];
            }
            lazy[indx] = 0;
        }
        
        // No overlap -> low high l r || l r low high
        if(high < l || low > r) return;
        
        // Complete overlap -> l low high r
        if(low >= l and high <= r){
            int node = (high - low + 1);
            seg[indx] += node * val;
            if(low != high){
                lazy[2 * indx + 1] += val;
                lazy[2 * indx + 2] += val;
            }
            return;
        }
        
        // Partial overlap
        int mid = (low + high) >> 1;
        update(2 * indx + 1, low, mid, l, r, val);
        update(2 * indx + 2, mid + 1, high, l, r, val);
        seg[indx] = seg[2 * indx + 1] + seg[2 * indx + 2];
    }
    
    int query(int indx, int low, int high, int l, int r){
        if(lazy[indx] != 0){
            int node = (high - low + 1);
            seg[indx] += (node * lazy[indx]);
            if(low != high){
                lazy[2 * indx + 1] += lazy[indx];
                lazy[2 * indx + 2] += lazy[indx];
            }
            lazy[indx] = 0;
        }
        
        // No overlap -> low high l r || l r low high
        if(high < l || r < low) return 0;
        
        // Complete overlap -> l low high r
        if(low >= l and high <= r){
            return seg[indx];
        }
        // Partial overlap
        int mid = (low + high) >> 1;
        int left = query(2 * indx + 1, low, mid, l, r);
        int right = query(2 * indx + 2, mid + 1, high, l, r);
        
        return left + right;
    }
};
