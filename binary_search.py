
number_list = [87, 576, 88, 800, 698, 645, 78, 9, 57, 7]

number_list.sort()


def binary_search(num_list: list, number, start, end):
    if start > end:
        return -1

    mid = (start + end) // 2
    if number == num_list[mid]:
        return mid
    elif number < num_list[mid]:
        return binary_search(num_list, number, start=start, end=mid - 1)
    else:
        return binary_search(num_list, number, start=mid + 1, end=end)


print(binary_search(number_list, 698, 0, len(number_list) - 1))
