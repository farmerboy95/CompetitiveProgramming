fun main(args: Array<String>) {
    var n = readLine()!!.toInt()
    var a = ArrayList<String> ()
    var m = 2 * n - 2
    for (i in 0..m-1) {
        a.add(readLine()!!)
    }

    if (n == 2) {
        println("PS")
        return
    }

    var possiblePrefix = ArrayList<Int> ()
    var possibleSuffix = ArrayList<Int> ()
    for (i in 0..m-1) {
        if (a[i].length == 1) {
            possiblePrefix.add(i)
        } else if (a[i].length == n-1) {
            possibleSuffix.add(i)
        }
    }

    for (i in possiblePrefix) {
        for (j in possibleSuffix) {
            var fullString = a[i] + a[j]
            var res = ArrayList<Char> ()
            for (u in 0..m-1) res.add(' ')
            var ok = true
            
            var prefix = ""
            for (x in 0..n-2) {
                prefix += fullString[x]
                var co = false
                for (u in 0..m-1)
                    if (res[u] == ' ' && prefix == a[u]) {
                        res[u] = 'P'
                        co = true
                        break;
                    }
                if (co == false) {
                    ok = false
                    break
                }
            }

            if (ok == false) {
                continue
            }

            var reversedFullString = fullString.reversed()
            var suffix = ""
            for (x in 0..n-2) {
                suffix += reversedFullString[x]
                var co = false
                for (u in 0..m-1)
                    if (res[u] == ' ' && suffix.reversed() == a[u]) {
                        res[u] = 'S'
                        co = true
                        break;
                    }
                if (co == false) {
                    ok = false
                    break
                }
            }

            if (ok == false) {
                continue
            }

            println(res.joinToString(""))
            return

        }
    }

}