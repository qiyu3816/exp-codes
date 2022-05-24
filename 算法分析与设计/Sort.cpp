#include <iostream>
#include <string>
#include <vector>

int partition(std::vector<int>& nums, int l, int r)
{
    int pivot = nums[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; ++j) {
        if (nums[j] <= pivot) {
            i = i + 1;
            std::swap(nums[i], nums[j]);
        }
    }
    std::swap(nums[i + 1], nums[r]);
    return i + 1;
}

int randomized_partition(std::vector<int>& nums, int l, int r)
{
    int i = rand() % (r - l + 1) + l;
    std::swap(nums[r], nums[i]);
    return partition(nums, l, r);
}

void randomized_quicksort(std::vector<int>& nums, int l, int r)
{
    if (l < r) {
        int pos = randomized_partition(nums, l, r);
        randomized_quicksort(nums, l, pos - 1);
        randomized_quicksort(nums, pos + 1, r);
    }
}

std::vector<int> sortArray(std::vector<int>& nums)
{
    srand((unsigned)time(NULL));
    randomized_quicksort(nums, 0, (int)nums.size() - 1);
    return nums;
}
