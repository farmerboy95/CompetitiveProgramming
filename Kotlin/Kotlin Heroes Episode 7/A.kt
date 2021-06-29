fun main(args: Array<String>) {
    var te = readLine()!!.toInt()
    for (o in 1..te) {
        var (n, k) = readLine()!!.split(" ").map({it.toInt()})
        var res = 0
        for (i in 1..n) {
            var (l, r) = readLine()!!.split(" ").map({it.toInt()})
            if (k > r) continue
            if (k >= l) res = maxOf(res, r - k + 1)
        }
        println(res)
    }
}