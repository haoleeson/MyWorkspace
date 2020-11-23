package LeetCode

import (
    "fmt"
    "testing"
)

func TestFindMinArrowShots(t *testing.T) {

    var points [][]int = [][]int{{9,12}, {1,10}, {4,11}, {8,12}, {3,9}, {6,9}, {6,7}}
    println("points:", points)
    fmt.Printf("min arrow shots: %d", findMinArrowShots(points))
}