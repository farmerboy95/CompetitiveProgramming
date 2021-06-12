fun main(args: Array<String>) {
    var (n, m) = readLine()!!.split(" ").map {it.toInt()}
    var a = readLine()!!.split(" ").map({it.toInt()})

    var sum = ArrayList<Int> ()
    sum.add(0)
    for (x in a) {
        sum.add(sum[sum.size-1] + x)
    }

    var q = readLine()!!.toInt()

    while (q-- > 0) {
        var w = readLine()!!.split(" ").map({it.toInt()})
        var lastDoor = 0
        for (i in 1..w[0]) {
            var empty = w[i]
            if (i > 1) {
                empty = empty - w[i-1] - 1
            } else {
                empty -= 1
            }

            var dau = lastDoor + 1
            var cuoi = n
            while (dau <= cuoi) {
                var mid = (dau + cuoi) / 2
                var sum = sum[mid] - sum[lastDoor]
                if (sum <= empty) dau = mid + 1
                else cuoi = mid - 1
            }

            lastDoor = cuoi
        }
        var remain = sum[n] - sum[lastDoor]
        if (remain <= m - w[w[0]]) {
            println("YES")
        } else {
            println("NO")
        }
    }
}
