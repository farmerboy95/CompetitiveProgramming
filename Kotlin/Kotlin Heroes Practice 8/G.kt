fun main(args: Array<String>) {
    var a = ArrayList<Int> ()
    for (i in 1..100) {
        a.add(i)
    }
    var b = ArrayList<Int> ()
    for (i in 1..100) {
        b.add(i * 128)
    }
    println("? " + a.joinToString(" "))
    System.out.flush()
    var p = readLine()!!.toInt()

    println("? " + b.joinToString(" "))
    System.out.flush()
    var q = readLine()!!.toInt()

    var x = 0

    x = x or (p and (((1 shl 7) - 1) shl 7))
    x = x or (q and ((1 shl 7) - 1))

    println("! ${x}")
    System.out.flush()
}
