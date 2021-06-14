fun getSumRange(l: Int, r: Int, sum: LongArray): Long {
    return sum[r] - sum[l-1]
}
 
fun getNum(l: Int, r: Int): Int {
    return r - l + 1
}
 
fun check(pos: Int, n: Int, m: Int, k: Int, a: IntArray, sum: LongArray, start: Int, end: Int, right: Int, w: Int): Long {
    var inc = pos.toLong() * getNum(start, w).toLong() - getSumRange(start, w, sum)
    var dec = 0L
    if (w + 1 <= right) {
        dec = getSumRange(w + 1, right, sum) - pos.toLong() * getNum(w + 1, right).toLong()
    }
    if (inc <= k) return inc + dec
    return -1
}
 
fun main(args: Array<String>) {
    var (n, m, k) = readLine()!!.split(" ").map({it.toInt()})
    // IntArray maps to Java's int[], and IntArray.sort() maps to Java's Array.sort(), 
    // so yes, it does use the unfortunately hack-vulnerable quicksort. Better to use 
    // Array<Int> or MutableList<Int> for sortings. (Same goes for LongArray and 
    // DoubleArray.) Kotlin also supports List<T>.sorted() for read-only lists, which 
    // will return a new list with the sorting applied.
    var arr = readLine()!!.split(" ").map({it.toInt()}).sorted().toIntArray()
    var a = IntArray(n + 1)
    var sum = LongArray(n + 1)
    sum[0] = 0
    a[0] = 0
 
    for (i in 1..n) {
        a[i] = arr[i-1]
    }
 
    for (i in 1..n) {
        sum[i] = sum[i-1] + a[i]
    }
 
    var res = 1000000000000000000L
    for (start in 1..(n-m+1)) {
        var end = start + m - 1
        var middle = (start + end) / 2
 
        var inc = a[middle].toLong() * getNum(start, middle).toLong() - getSumRange(start, middle, sum)
        var dec = getSumRange(middle, end, sum) - a[middle].toLong() * getNum(middle, end).toLong()
        if (inc <= k) {
            res = minOf(res, inc + dec)
            continue
        }
 
        var dau = start
        var cuoi = middle
        while (dau <= cuoi) {
            var mid = (dau + cuoi) / 2
            inc = a[mid].toLong() * getNum(start, mid).toLong() - getSumRange(start, mid, sum)
            if (inc <= k) dau = mid+1
            else cuoi = mid-1
        }
        var w = cuoi
 
        dau = a[cuoi]
        cuoi = a[cuoi+1]
        while (dau <= cuoi) {
            var mid = (dau + cuoi) / 2
            if (check(mid, n, m, k, a, sum, start, middle, end, w) >= 0) dau = mid+1
            else cuoi = mid-1
        }
 
        var x = check(cuoi, n, m, k, a, sum, start, middle, end, w)
        
        res = minOf(res, x)
    }
    println(res)
    
}