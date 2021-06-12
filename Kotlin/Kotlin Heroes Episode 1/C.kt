fun main(args: Array<String>) {
    var te = readLine()!!.toInt()
    while (te-- > 0) {
        var s = readLine()!!
        var t = readLine()!!

        var i = 0
        var j = 0
        while (j < t.length) {
            if (i >= s.length) {
                break
            }
            if (s[i] == t[j]) {
                i++
                j++
            } else {
                if (s[i] == '+' && t[j] == '-') {
                    break
                }
                if (i+1 >= s.length) {
                    break
                }
                if (s[i+1] == '-') {
                    i += 2
                    j++
                } else {
                    break
                }
            }
        }
        if (i < s.length || j < t.length) {
            println("NO")
        } else {
            println("YES")
        }
    }
}
