fun main(args: Array<String>) {
    var te = readLine()!!.toInt()
    for (o in 1..te) {
        var (n, k) = readLine()!!.split(" ").map { it.toInt() }

        var res = ""
        for (i in 0..n-1) {
            var letter = i % k
            var x : Char = 'a' + letter
            res += x
        }
        println(res)
    }
}