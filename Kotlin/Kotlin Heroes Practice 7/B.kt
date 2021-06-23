fun main(args: Array<String>) {
    var te = readLine()!!.toInt()
    for (o in 1..te) {
        var (a, b, k) = readLine()!!.split(" ").map { it.toLong() }
        var right = k / 2 + k % 2
        var left = k / 2
        println("${right * a - left * b}")
    }
}