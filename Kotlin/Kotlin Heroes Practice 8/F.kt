fun main(args: Array<String>) {
    var (n, m) = readLine()!!.split(" ").map { it.toInt() }
    var a = ArrayList<ArrayList<Int>> ()
    var mark = ArrayList<ArrayList<Int>> ()
    for (i in 1..n) {
        a.add(ArrayList<Int> ())
        mark.add(ArrayList<Int> ())
        var b = readLine()!!.split(" ").map({ it.toInt() })
        for (j in 0..m-1) {
            a[i-1].add(b[j])
            mark[i-1].add(0)
        }
    }

    var res = ArrayList<Pair<Int, Int>>()
    for (i in 0..n-2) {
        for (j in 0..m-2) {
            if (a[i][j] == 1 && a[i+1][j] == 1 && a[i][j+1] == 1 && a[i+1][j+1] == 1) {
                res.add(Pair(i+1, j+1))
                mark[i][j] = 1
                mark[i][j+1] = 1
                mark[i+1][j] = 1
                mark[i+1][j+1] = 1
            }
        }
    }

    var ok = 1
    for (i in 0..n-1) {
        for (j in 0..m-1) {
            if (a[i][j] == 1 && mark[i][j] == 0) {
                ok = 0
            }
        }
    }

    if (ok == 0) {
        println("-1")
    } else {
        println(res.size)
        for (i in 0..res.size-1) {
            println("${res[i].first} ${res[i].second}")
        }
    }
}