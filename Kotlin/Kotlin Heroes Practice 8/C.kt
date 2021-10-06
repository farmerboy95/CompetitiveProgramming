fun main(args: Array<String>) {
    var n = readLine()!!.toInt()
    var a = readLine()!!.split(" ").map({ it.toInt() })

    var b = ArrayList<Pair<Int, Int>>()
    for (i in 0..n-1) {
        var pair = Pair(a[i], i)
        b.add(pair)
    }

    var sortedList = b.sortedWith(compareBy({it.first}, {it.second})).asReversed()
    var kq = ArrayList<Int>()
    var res = 0
    var destroyed = 0
    for (i in 0..n-1) {
        kq.add(sortedList[i].second + 1)
        res += sortedList[i].first * destroyed + 1
        destroyed++
    }

    println(res)
    println(kq.joinToString(" "))
}
