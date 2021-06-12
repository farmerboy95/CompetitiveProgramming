fun main(args: Array<String>) {
    var te = readLine()!!.toInt()
    for (o in 1..te) {
        var (x, y) = readLine()!!.split(" ").map { it.toInt() }
        var k = minOf(x, y) - 1
        println("${x-k} $k ${y-k}")
    }
}
