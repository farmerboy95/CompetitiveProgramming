#include <vector>
using namespace std;

int quickSelectHelper(vector<int> &a, int l, int r, int pos) {
    while (1) {
        int pivot = l;
        int left = l+1, right = r;
        while (left <= right) {
            if (a[left] > a[pivot] && a[pivot] > a[right]) swap(a[left], a[right]);
            if (a[left] <= a[pivot]) left++;
            if (a[right] >= a[pivot]) right--;
        }
        swap(a[pivot], a[right]);
        if (right == pos) {
            return a[right];
        } else if (pos < right) {
            r = right-1;
        } else {
            l = right+1;
        }
    }
}

int quickselect(vector<int> array, int k) {
    return quickSelectHelper(array, 0, array.size()-1, k-1);
}
