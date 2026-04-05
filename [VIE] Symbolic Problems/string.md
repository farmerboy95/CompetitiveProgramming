# String

## Tìm xâu con trong một xâu khác

Input: Một văn bản t và một xâu s. 

Output: Vị trí của tất cả các lần xuất hiện của xâu s trong văn bản t.

Solution:
- KMP trên xâu s
- Duyệt t và KMP trên đó
- O(|s| + |t|)

## Đếm số lần xuất hiện của mỗi tiền tố

Input: Một xâu s có độ dài n. 

Output: Đếm số lần xuất hiện của mỗi tiền tố s[0..i] trong chính xâu đó. 

Solution:
- KMP trên xâu s -> pi[i] = độ dài tiền tố dài nhất mà cũng là hậu tố của s[0..i], không tính chính xâu s[0..i]
- Gọi res[i] (i:0->n) là số lần xuất hiện của tiền tố độ dài i trong chính xâu s.
- Duyệt mỗi i trên xâu s, thêm 1 vào res[pi[i]].
- Duyệt ngược từ n-1 đến 1, res[pi[i-1]] += res[i]
- Cuối cùng, mỗi tiền tố cần được thêm vào đáp án, res[i]++ (i:0->n)
- O(|s|)

Biến thể: cho thêm một xâu t và ta muốn đếm số lần xuất hiện của mỗi tiền tố s[0..i] trong t.

Solution:
- Tính KMP cho xâu s+#+t, sau đó tính y như trên với các pi[i] mà i >= |s|+1
- O(|s| + |t|)

## Nén xâu

Input: Cho một xâu s có độ dài n.

Output: Ta muốn tìm biểu diễn "nén" ngắn nhất của xâu, tức là ta muốn tìm xâu t có độ dài nhỏ nhất sao cho s có thể được biểu diễn dưới dạng nối một hoặc nhiều bản sao của t.

Solution: 
- KMP cho s -> pi[i] = độ dài tiền tố dài nhất mà cũng là hậu tố của s[0..i], không tính chính xâu s[0..i]
- Sử dụng giá trị cuối cùng, ta định nghĩa k = n - pi[n - 1].
- Nếu n chia hết cho k, thì k là đáp án, ngược lại không có cách nén hiệu quả và đáp án là n.
- O(|s|)

## Số lượng xâu con khác nhau trong một xâu

Input: Cho một xâu s có độ dài n.

Output: In ra số lượng xâu con khác nhau trong xâu s.

Solution:
- Gọi k là số lượng xâu con khác nhau hiện tại trong s, và ta thêm ký tự c vào cuối s. Rõ ràng một số xâu con mới kết thúc bằng c sẽ xuất hiện. Ta muốn đếm các xâu con mới này mà chúng chưa từng xuất hiện trước đó.
- Ta lấy xâu t = s + c và đảo ngược lại. Giờ bài toán trở thành tính xem có bao nhiêu tiền tố không xuất hiện ở bất kỳ đâu khác.
- O(|s|^2)

## Tìm xâu con trong một xâu khác có chứa wildcard

Link: https://codeforces.com/contest/808/problem/G

Input: Một văn bản t và một xâu s, t có chứa các ký tự wildcard (match ký tự nào cũng được), s thì không

Output: Số lượng lớn nhất có thể mà s nằm trong t.

Solution:
- KMP trên xâu s -> pi[i] = độ dài tiền tố dài nhất mà cũng là hậu tố của s[0..i], không tính chính xâu s[0..i]
- Gọi dp[i][j] = số lần lớn nhất có thể mà s nằm trong đoạn t[0..i-1] mà lần cuối cùng đang match dở dang s[0..j-1] với t[i-j..i-1].
- Với mỗi bước, ta cần phải thử s[j] với t[i], có 2 trường hợp:
    + s[j] == t[i] (nghĩa là trùng hoặc t[i] là wildcard), ta có thể đi đến dp[i+1][j+1] (khi j < |s|-1) hoặc dp[i+1][pi[j]] (khi j = |s|-1)
    + s[j] != t[i] (không trùng hoặc t[i] là wildcard nhưng ta không match nó với s[j]), ta có thể đi đến dp[i][pi[j-1]] (khi j > 0) hoặc dp[i+1][0] (khi j = 0), nhớ duyệt ngược lại để không tính nhiều lần.
- O(|s| * |t|)