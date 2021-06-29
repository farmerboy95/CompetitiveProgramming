fun main(args: Array<String>) {
    var s = readLine()!!
    var n = s.length
    s = " " + s
 
    var cnt = ArrayList<Int> ()
    for (i in 0..n) cnt.add(0)
 
    for (i in 1..n)
        if (s[i] == '1') {
            cnt[i] = cnt[i-1] + 1
        } else {
            cnt[i] = cnt[i-1]
        }
    
    var res = ArrayList<Int> ()
    var co1 = false
    for (i in 1..n) {
        if (co1) {
            res.add(1)
            continue
        }
        var now = 0
        var kq = 0
        while (now + 1 <= n) {
            var dau = now+1
            var cuoi = n
            while (dau <= cuoi) {
                var mid = (dau + cuoi) / 2
                var dem = minOf(cnt[mid] - cnt[now], mid - now - (cnt[mid] - cnt[now]))
                if (dem > i) cuoi = mid-1
                else dau = mid+1
            }
            kq++
            now = cuoi
        }
        res.add(kq)
        if (kq == 1) {
            co1 = true
        }
    }
 
    println(res.joinToString(" "))
    
}