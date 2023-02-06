// Code for finding the min between given range and updating the value for the given index in less time complexity

#include<bits/stdc++.h>
using namespace std;

class SEGTree
{
public:
    vector<int> seg;
    SEGTree(int n){
        seg.resize(4*n);

    }

    // Time complexity =  O(4N) ~ O(N)
    void build(int indx, int low, int high, vector<int> &arr){
        if(low == high){
            seg[indx] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * indx + 1, low, mid, arr);
        build(2 * indx + 2, mid + 1, high, arr);
        seg[indx] = min(seg[2 * indx + 1], seg[2 * indx + 2]);
    }
   
   // Time complexity = if the l and r is small then we will find the node is completely outside the range l r so the complexity will be O(logN)
   //                   if the l and r is large then we will find the node lies completely inside the range l r so the complexity will be O(logN)
   //                   if the l and r is in the middle so we will have to traverse in both the child hence the complexity will be O(4N) ~ O(N)                  
    int query(int indx, int low, int high, int l, int r, vector<int> &arr){
        // low and high are the ranges for the nodes and l and r are the ranges for the queries for which minimum has to be found

        // Node is completely outside -> low high l r or l r low high

        if(high < l || low > r) return INT_MAX;

        // Node completely lies inside the given range l r -> l low high r

        if(low >= l and high <= r) return seg[indx];

        // Node partial lies inside the range -> go on the both sides

        int mid = (low + high) >> 1;
        int left = query(2 * indx + 1, low, mid, l, r, arr);
        int right = query(2 * indx + 2, mid + 1, high, l, r, arr);

        return min(left, right);
    }

    // Time complexity = O(logN)
    void update(int indx, int low, int high, int i, int val){
        // Update to be done at index i with the value val
        if(low == high){
            seg[indx] = val;
            return;
        }

        int mid = (high + low) >> 1;

        if(i <= mid){
            update(2 * indx + 1, low, mid, i, val);
        }
        else{
            update(2 * indx + 2, mid + 1, high, i, val);
        }

        // update after updating the value
        seg[indx] = min(seg[2 * indx + 1], seg[2 * indx + 2]);
    }
};
