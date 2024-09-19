/*
No2332.the-latest-time-to-catch-a-bus
*/

func latestTimeCatchTheBus(buses []int, passengers []int, capacity int) int {
    m := len(buses)
    n := len(passengers)
    sort.Ints(buses)
    sort.Ints(passengers)

    // double pointer
    var i, j int = 0, 0
    var k int
    for ; i < m; i++ {
        k = capacity
        for j < n && buses[i] >= passengers[j] && k > 0 {
            j++
            k--
        }
    }

    j--
    var lastArrive = buses[m-1]
    if k <= 0 {
        // the last in bus passenger
        lastArrive = passengers[j]
    }
    for j >= 0 && passengers[j] == lastArrive {
        j--
        lastArrive--
    }

    return lastArrive
}
