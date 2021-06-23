fun main(args: Array<String>) {
    var te = readLine()!!.toInt()
    for (o in 1..te) {
        var (x, y) = readLine()!!.split(" ").map { it.toInt() }
        println("${x+y}")
    }
}