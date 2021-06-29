fun main(args: Array<String>) {
    var te = readLine()!!.toInt()
    for (o in 1..te) {
        var (n, k) = readLine()!!.split(" ").map({it.toInt()})
        var s = readLine()!!
        
        var eaten = ArrayList<Int> ()
        for (i in 0..n-1) eaten.add(0)
 
        var likes = 0
        for (i in 0..n-1)
            if (s[i] == '1') likes++
 
        var now = 0
        var res = 0
        if (likes > 0) {
            while (true) {
                eaten[now] = 1
                if (s[now] == '1') likes--
                res++
                if (likes == 0) break
 
                var cnt = k
                while (true) {
                    now = (now + 1) % n
                    if (eaten[now] == 0) {
                        cnt--
                    }
                    if (cnt == 0) {
                        break
                    }
                }
            }
        }
 
        println(res)
    }
 
}