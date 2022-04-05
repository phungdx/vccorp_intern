def firstMissingPositive(nums):
    N = len(nums)
    arr = [0 for _ in range(N)]

    for i in range(N):
        if 0 < nums[i] <= N:
            arr[nums[i] - 1] += 1

    for i in range(N):
        if arr[i] == 0:
            return i+1
    return N+1

if __name__ == '__main__':
    nums1 = [1,2,3,4,5,6,7,8]
    nums2 = [2, 3, -7, 6, 8, 1, -10, 15]
    nums3 = [1, 1, 0, -1, -2]
    nums4 = [3,4,-1,1]
    nums5 = [-1, -3, -4]
    print(firstMissingPositive(nums1))