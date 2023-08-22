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

def quickSort(arr, left=None, right=None):
    left = 0 if not isinstance(left,(int, float)) else left
    right = len(arr)-1 if not isinstance(right,(int, float)) else right
    if left < right:
        partitionIndex = partition(arr, left, right)
        quickSort(arr, left, partitionIndex-1)
        quickSort(arr, partitionIndex+1, right)
    return arr

def partition(arr, left, right):
    pivot = left
    index = pivot+1
    i = index
    while i <= right:
        if arr[i] < arr[pivot]:
            swap(arr, i, index)
            index+=1
        i+=1
    swap(arr,pivot,index-1)
    return index-1

def swap(arr, i, j):
    arr[i], arr[j] = arr[j], arr[i]

nums = [4,5,1,6,2,7,3,8]
quickSort(nums, 0, len(nums)-1)
print(nums)