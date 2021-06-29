fun main(args: Array<String>) {
    var te = readLine()!!.toInt()
    for (o in 1..te) {
        var n = readLine()!!.toInt()
        var x = readLine()!!.split(" ").map({it.toInt()})
        
        var co = true
        for (i in 1..n-1) {
            var diff = x[i] - x[i-1]
            if (diff % 2 == 0) {
                co = false
                break;
            }
        }
        if (!co) println("YES")
        else println("NO")
    }
}