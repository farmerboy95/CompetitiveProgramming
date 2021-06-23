fun main(args: Array<String>) {
    var n = readLine()!!.toInt()
    var a = readLine()!!.split(" ").map({ it.toInt() })

    var res = ArrayList<Int> ()

    var posMax = -1
    var posSecondMax = -1
    var sum : Long = 0
    for (i in 0..n-1) {
        if (posMax == -1 || a[posMax] < a[i]) {
            if (posMax != -1) posSecondMax = posMax
            posMax = i
        } else if (posSecondMax == -1 || a[posSecondMax] < a[i]) {
            posSecondMax = i
        }
        sum += a[i]
    }

    for (i in 0..n-1) {
        if (i == posMax) {
            var remain : Long = sum - a[i] - a[posSecondMax]
            if (remain != a[posSecondMax].toLong()) continue
        } else {
            var remain : Long = sum - a[i] - a[posMax]
            if (remain != a[posMax].toLong()) continue
        }
        res.add(i+1)
    }

    println(res.size)
    println(res.joinToString(" "))
}