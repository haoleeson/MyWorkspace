/*
No2181.merge-nodes-in-between-zeros
*/

func mergeNodes(head *ListNode) *ListNode {
    var res *ListNode = &ListNode{}
    var p, k *ListNode = head.Next, res
    var tmp int = 0

    for ; p != nil; p = p.Next {
        if p.Val != 0 {
            tmp += p.Val
        } else {
            k.Next = &ListNode{
                Val: tmp,
                Next: nil,
            }
            k = k.Next
            tmp = 0
        }
    }

    return res.Next
}
