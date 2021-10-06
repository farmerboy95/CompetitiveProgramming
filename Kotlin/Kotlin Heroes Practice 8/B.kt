fun main(args: Array<String>) {
    var a1 = readLine()!!.toInt()
    var a2 = readLine()!!.toInt()
    var k1 = readLine()!!.toInt()
    var k2 = readLine()!!.toInt()
    var n = readLine()!!.toInt()
    
    var x = 0
    var y = 0

    var lim = a1 * (k1 - 1) + a2 * (k2 - 1)
    if (n <= lim) {
        x = 0
    } else {
        var remain = n - lim
        var lim2 = a1 + a2;
        x = minOf(remain, lim2)
    }

    if (k2 < k1) {
        k1 = k2.also {k2 = k1}
        a1 = a2.also {a2 = a1}
    }
    if (n <= k1 * a1) {
        y = n / k1
    } else {
        y = a1
        n -= k1 * a1
        if (n <= k2 * a2) {
            y += n / k2
        } else {
            y += a2
        }
    }

    println("${x} ${y}")
}
