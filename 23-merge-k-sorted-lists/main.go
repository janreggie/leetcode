package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func mergeKLists(lists []*ListNode) *ListNode {
	k := len(lists)
	if k == 0 {
		return nil
	}
	if k == 1 {
		return lists[0]
	}
	toMerge := make([]*ListNode, (k+1)/2)

	for ii := 0; ii < k; ii += 2 {
		l1 := lists[ii]
		var l2 *ListNode
		if ii+1 < k {
			l2 = lists[ii+1]
		}
		toMerge[ii/2] = mergeTwo(l1, l2)
	}

	return mergeKLists(toMerge)
}

func mergeTwo(l1, l2 *ListNode) *ListNode {
	if l1 == nil {
		return l2
	}
	if l2 == nil {
		return l1
	}

	if l1.Val < l2.Val {
		l1.Next = mergeTwo(l1.Next, l2)
		return l1
	}

	l2.Next = mergeTwo(l1, l2.Next)
	return l2
}

func main() {
	// Do needful here sir
}
