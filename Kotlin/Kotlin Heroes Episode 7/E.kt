fun main(args: Array<String>) {
    var n = readLine()!!.toInt()
    var a = readLine()!!.split(" ").map({it.toInt()}).sorted().toIntArray() // n elements
    var b = readLine()!!.split(" ").map({it.toInt()}).sorted().toIntArray() // n+1 elements
    var m = readLine()!!.toInt()
    var c = readLine()!!.split(" ").map({it.toInt()}) // m elements
 
    var res = ArrayList<Int> ()
    var l = ArrayList<Int> ()
    for (i in 1..n+1) l.add(0)
    var r = ArrayList<Int> ()
    for (i in 1..n+1) r.add(0)
 
    for (i in 0..n-1) l[i] = b[i] - a[i]
    for (i in n downTo 1) r[i] = b[i] - a[i-1]
 
    for (i in 1..n-1) l[i] = maxOf(l[i], l[i-1])
    for (i in n-1 downTo 1) r[i] = maxOf(r[i], r[i+1])
 
    for (i in 0..m-1) {
        var dau = 0
        var cuoi = n-1
        while (dau <= cuoi) {
            var mid = (dau + cuoi) / 2
            if (a[mid] <= c[i]) dau = mid+1
            else cuoi = mid-1
        }
        var now = -2000000010
        if (dau > 0) now = maxOf(now, l[dau-1])
        if (dau < n) now = maxOf(now, r[dau+1])
        now = maxOf(now, b[dau] - c[i])
        res.add(now)
    }
    println(res.joinToString(" "))
}