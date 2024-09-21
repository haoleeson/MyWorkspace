/*
No2374.node-with-highest-edge-score
*/

func edgeScore(edges []int) int {
    n := len(edges)
    cnt := make([]int, n)

    maxA := 0
    maxNode := 0

    for i:=0; i< n; i++ {
        cnt[edges[i]] += i
        if cnt[edges[i]] > maxA {
            maxA = cnt[edges[i]]
            maxNode = edges[i]
        } else if cnt[edges[i]] == maxA {
            maxNode = min(maxNode, edges[i])
        }
    }

    return maxNode
}