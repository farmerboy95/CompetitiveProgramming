fun main(args: Array<String>) {
    var (n, m) = readLine()!!.split(" ").map({it.toInt()})
    var hashMap : HashMap<String, Int> = HashMap<String, Int> ()
 
    for (i in 1..n) {
        var str = readLine()!!
        hashMap.put(str, i)
    }
 
    var q = readLine()!!.toInt()
    for (o in 1..q) {
        var str = readLine()!!
        var prefix = ArrayList<String> ()
        var now = ""
        prefix.add(now)
        for (i in 0..m-1) {
            now += str[i]
            prefix.add(now)
        }
        var suffix = ArrayList<String> ()
        var reversedStr = str.reversed()
        now = ""
        suffix.add(now)
        for (i in 0..m-1) {
            now += reversedStr[i]
            suffix.add(now.reversed())
        }
 
        var mutableSet = mutableSetOf<Int?>()
        for (i in 0..m) {
            var w = prefix[i] + suffix[m-i]
            var z : Int? = hashMap.get(w)
            if (z != null) {
                var p = hashMap[w]
                mutableSet.add(p)
            }
        }
        println(mutableSet.size)
    }
}