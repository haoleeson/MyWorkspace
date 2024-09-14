/*
No2398.maximum-number-of-robots-within-budget
*/

func maximumRobots(chargeTimes []int, runningCosts []int, budget int64) int {
    n := len(chargeTimes)
    res := 0
    runningCostSum := int64(0)
    var q []int

    // double pointer
    // iteor r
    for l, r := 0, 0; r < n; r++ {
        runningCostSum += int64(runningCosts[r])

        // single del queue
        // delete letter tail nums' index
        for len(q) > 0 && chargeTimes[q[len(q)-1]] <= chargeTimes[r] {
            q = q[:len(q)-1]
        }
        // add new index
        q = append(q, r)

        // move  budget
        for l <=r && int64(r-l+1) * runningCostSum + int64(chargeTimes[q[0]]) > budget {
            // if l is biggest, remove l
            if len(q) > 0 && q[0] == l {
                q = q[1:]
            }
            runningCostSum -= int64(runningCosts[l])
            // move l
            l++
        }
        res = max(res, r-l+1)
    } 
    return res
}