import java.util.*

fun main(args: Array<String>) {
    var n = readLine()!!.toInt()
    var a = readLine()!!.split(" ").map({it.toInt()})

    var m = 0
    for (x in a) {
        if (x == -1) {
            m++
        }
    }
    
    var i = 0
    var nowLen = m
    var res = ArrayList<ArrayList<Int>> ()
    for (i in 1..m) {
        res.add(ArrayList<Int> ())
    }

    var que = LinkedList<Int> ()
    for (i in 0 until m) {
        que.offer(i)
    }

    for (x in a) {
        var u = que.poll()
        if (x != -1) {
            res[u].add(x)
            que.offer(u)
        }
    }

    println(m)
    for (i in res) {
        println("${i.size} ${i.joinToString(" ")}")
    }
}
