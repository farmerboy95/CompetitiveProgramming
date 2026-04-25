# Median

## Xét xem x có phải median của đoạn [l..r] hay không

Input: Một đoạn con [l..r] của một mảng a và một số x

Output: true/false, x có phải median của đoạn hay không

Solution:
- Ta tiền xử lý bằng cách tạo mảng c
    + c[i] = 0 khi a[i] = x
    + c[i] = -1 khi a[i] < x
    + c[i] = 1 khi a[i] > x
- Sau đó tạo prefix sum trên mảng c
- Như vậy với đoạn [l..r], ta dễ dàng tìm được số các số nhỏ hơn, lớn hơn x, bằng x, và x là median khi số số nhỏ hơn x và số số lớn hơn x không vượt quá giới hạn median, và có ít nhất một số bằng x trong đoạn.
