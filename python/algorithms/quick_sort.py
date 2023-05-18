def quick_sort(nums, l, r):
    if l >= r: return
    i, j = l, r
    pivot = nums[l]
    while i < j:
        while i < j and nums[j] >= pivot: j -= 1
        while i < j and nums[i] <= pivot: i += 1
        nums[i], nums[j] = nums[j], nums[i]
    nums[l], nums[i] = nums[i], nums[l]
    quick_sort(nums, l, i-1)
    quick_sort(nums, i+1, r)

nums = [4,5,1,6,2,7,3,8]
quick_sort(nums, 0, len(nums)-1)
print(nums)