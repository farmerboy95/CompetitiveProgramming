// Idea: https://codeforces.com/blog/entry/92357
// Do not use the literal Stack, it will cause TLE

fun main(args: Array<String>) {
    var (n, m) = readLine()!!.split(" ").map({it.toInt()})
    var s = ArrayList<String> ()
    for (i in 1..n) {
        var str = readLine()!!
        s.add(str)
    }
    
    var res = LongArray(1 shl 5)

    for (mask in 1..31) {
        var a = ArrayList<ArrayList<Int>> ()
        var cnt = 0

        for (i in 0..4) {
            if ((mask and (1 shl i)) > 0) {
                cnt++
            }
        }

        for (i in 0..n-1) {
            var b = ArrayList<Int> ()
            for (j in 0..m-1) {
                var num = 0
                if (s[i][j] == 'A') num = 1
                if (s[i][j] == 'B') num = 2
                if (s[i][j] == 'C') num = 4
                if (s[i][j] == 'D') num = 8
                if (s[i][j] == 'E') num = 16
                if ((mask and num) > 0) {
                    b.add(1)
                } else {
                    b.add(0)
                }
            }
            a.add(b)
        }

        for (i in 1..n-1) {
            for (j in 0..m-1) {
                if (a[i][j] > 0) {
                    a[i][j] += a[i-1][j]
                }
            }
        }

        var sum : Long = 0

        for (i in 0..n-1) {
            val l = IntArray(m) { -1 }
            val q = IntArray(m) { 0 }
            var ptr = -1
            for (j in 0..m-1) {
                while (ptr >= 0 && a[i][j] <= a[i][q[ptr]]) ptr--
                if (ptr >= 0) l[j] = q[ptr]
                ptr++
                q[ptr] = j
            }
            val r = IntArray(m) { m }
            ptr = -1
            for (j in m-1 downTo 0) {
                while (ptr >= 0 && a[i][j] < a[i][q[ptr]]) ptr--
                if (ptr >= 0) r[j] = q[ptr]
                ptr++
                q[ptr] = j
            }

            for (j in 0..m-1) {
                sum += (j - l[j]).toLong() * (r[j] - j).toLong() * a[i][j].toLong()
            }
        }
        res[mask] = sum
    }

    for (mask1 in 1..31)
        for (mask2 in (mask1+1)..31)
            if ((mask2 and mask1) == mask1) res[mask2] -= res[mask1]

    val ans = LongArray(6) { 0 }
    for (mask in 1 until (1 shl 5)) ans[mask.countOneBits()] += res[mask]
    
    println(ans.drop(1).joinToString(" "))
}