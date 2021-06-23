fun main(args: Array<String>) {
    var n = readLine()!!.toInt()
    var a = readLine()!!.split(" ").map({ it.toInt() }).sorted().toIntArray()

    var res = 0
    for (i in 0..n-1) {
        if (i % 2 == 1) continue
        res += a[i+1] - a[i]
    }
    println(res)
}