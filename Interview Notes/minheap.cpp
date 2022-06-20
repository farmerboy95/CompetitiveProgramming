#include <vector>
using namespace std;

// Do not edit the class below except for the buildHeap,
// siftDown, siftUp, peek, remove, and insert methods.
// Feel free to add new properties and methods to the class.
class MinHeap {
public:
    vector<int> heap;

    MinHeap(vector<int> vector) { heap = buildHeap(vector); }

    vector<int> buildHeap(vector<int> &vector) {
        int n = vector.size();
        int firstParentIdx = (n - 2) / 2;
        for (int i = firstParentIdx; i >= 0; i--) {
            siftDown(i, n-1, vector);
        }
        return vector;
    }

    void siftDown(int currentIdx, int endIdx, vector<int> &heap) {
        int leftIdx = currentIdx * 2 + 1;
        while (leftIdx <= endIdx) {
            int rightIdx = currentIdx * 2 + 2;
            if (rightIdx > endIdx) {
                rightIdx = -1;
            }
            int idxToSwap = 0;
            if (rightIdx != -1 && heap[rightIdx] < heap[leftIdx]) {
                idxToSwap = rightIdx;
            } else {
                idxToSwap = leftIdx;
            }
            if (heap[idxToSwap] < heap[currentIdx]) {
                swap(heap[idxToSwap], heap[currentIdx]);
                currentIdx = idxToSwap;
                leftIdx = currentIdx * 2 + 1;
            } else {
                return;
            }
        }
    }

    void siftUp(int currentIdx, vector<int> &heap) {
        int parentIdx = (currentIdx - 1) / 2;
        while (currentIdx > 0 && heap[currentIdx] < heap[parentIdx]) {
            swap(heap[currentIdx], heap[parentIdx]);
            currentIdx = parentIdx;
            parentIdx = (currentIdx - 1) / 2;
        }
    }

    int peek() {
        return heap[0];
    }

    int remove() {
        swap(heap[0], heap[heap.size() - 1]);
        int val = heap.back();
        heap.pop_back();
        int n = heap.size();
        siftDown(0, n-1, heap);
        return val;
    }

    void insert(int value) {
        heap.push_back(value);
        int n = heap.size();
        siftUp(n - 1, heap);
    }
};
