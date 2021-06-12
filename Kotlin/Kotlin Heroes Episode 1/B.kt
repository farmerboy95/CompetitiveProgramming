fun main(args: Array<String>) {
    var n = readLine()!!.toInt()
    var a = readLine()!!.split(" ").map({it.toInt()})

    var max2 = 0
    var max1 = 0

    var cnt = 0
    for (x in a) {
        if (x >= max1) {
            max2 = max1
            max1 = x
        } else if (x >= max2) {
            max2 = x
        } else {
            cnt++
        }
    }
    println(cnt)
}
