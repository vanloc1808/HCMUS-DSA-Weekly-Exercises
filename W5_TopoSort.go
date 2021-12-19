package main

import "fmt"

type Trailor struct {
	ID   *Leader
	Next *Trailor
}

type Leader struct {
	Key    int      // Key of Node
	Count  int      // Number of precedences
	Next   *Leader  // Pointer to next Node
	Trails *Trailor // Pointer to list of Trailor
}

func find(head *Leader, tail **Leader, x int) *Leader { // Simply find or addTail
	p := head
	(*tail).Key = x
	for p.Key != x {
		p = p.Next
	}

	if p == *tail { // Not found
		p.Next = &Leader{0, 0, nil, nil} // create new sentinel
		*tail = p.Next
	}
	return p
}

func splitZeroFromList(head **Leader, tail *Leader) {
	curr := *head
	next := curr
	*head = nil        // Create virtual list with count of zeros
	for next != tail { // Not include tail node
		curr = next
		next = next.Next
		if curr.Count == 0 {
			// add head new list
			curr.Next = *head
			*head = curr
		}
	}
}

// x < y aka x -> y
func input(head *Leader, tail **Leader, x int, y int) {
	// Find and insert to list
	xNode := find(head, tail, x)
	yNode := find(head, tail, y)
	// Add Trailor by add head
	t := &Trailor{yNode, xNode.Trails}
	xNode.Trails = t
	// Increase number of precedences
	yNode.Count += 1
}

func TopoSort(head **Leader, tail *Leader) {
	splitZeroFromList(head, tail)
	p := *head

	for p != nil {
		fmt.Println(p.Key)
		t := p.Trails
		p = p.Next
		for t != nil { // Iterate through trailors
			succNode := t.ID

			// Remove p (previous p), so all successor decrease count by 1
			succNode.Count -= 1
			// If it's has count of zero -> move it to previous of p (current p)
			if succNode.Count == 0 { // Add head (head at p)
				succNode.Next = p
				p = succNode
			}

			t = t.Next
		}
	}
}

func main() {
	head := &Leader{0, 0, nil, nil} // Dummy node
	tail := head                    // Also the sentinel

	input(head, &tail, 1, 2)
	input(head, &tail, 2, 4)
	input(head, &tail, 4, 6)
	input(head, &tail, 2, 10)
	input(head, &tail, 4, 8)
	input(head, &tail, 6, 3)
	input(head, &tail, 1, 3)
	input(head, &tail, 3, 5)
	input(head, &tail, 5, 8)
	input(head, &tail, 7, 5)
	input(head, &tail, 7, 9)
	input(head, &tail, 9, 4)
	input(head, &tail, 9, 10)

	TopoSort(&head, tail)

}
