fun main(args: Array<String>) {
    var n = readLine()!!.toInt()
    var hashMap = HashMap<Int, Int>()

    var res = 0
    while (true) {
        var z : Int? = hashMap.get(n)
        if (z != null) {
            break
        }
        res++
        hashMap[n] = 1
        n++
        while (n % 10 == 0) {
            n /= 10
        }
    }
    println(res)
}
