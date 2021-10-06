fun main(args: Array<String>) {
    var t = readLine()!!.toInt()
    for (o in 1..t) {
        var (a, b) = readLine()!!.split(" ").map({it.toInt()})
        println(a+b)
    }
}
