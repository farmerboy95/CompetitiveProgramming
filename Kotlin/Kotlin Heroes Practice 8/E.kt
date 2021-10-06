fun main(args: Array<String>) {
    var te = readLine()!!.toInt()
    for (o in 1..te) {
        var s = readLine()!!
        var a = ArrayList<Pair<Int, Char>>()

        var n = s.length

        var cnt = 1
        for (i in 1..n-1) {
            if (s[i] == s[i-1]) {
                cnt++
            } else {
                a.add(Pair(cnt, s[i-1]))
                cnt = 1
            }
        }
        a.add(Pair(cnt, s[n-1]))

        var l = -1
        var r = -1
        for (i in 0..(a.size-1)) {
            if (a[i].second == '1') {
                l = i
                break
            }
        }

        if (l == -1) {
            println("0")
            continue
        }

        for (i in (a.size-1) downTo 0) {
            if (a[i].second == '1') {
                r = i
                break
            }
        }

        var res = 0
        for (i in l..r) {
            if (a[i].second == '0') {
                res += a[i].first
            }
        }

        println(res)
    }
}
