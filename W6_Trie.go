package main

import "fmt"

type TrieNode struct {
	ID   int
	next map[byte]*TrieNode
}

func CreateNode() *TrieNode {
	return &TrieNode{-1, make(map[byte]*TrieNode)}
}

func (t *TrieNode) Insert(s string, id int) {
	p := t
	for i := range s {
		var c byte = s[i]
		if p.next[c] == nil {
			p.next[c] = CreateNode()
		}
		p = p.next[c]
	}
	p.ID = id
}

func (t *TrieNode) Search(s string) int {
	p := t
	for i := range s {
		var c byte = s[i]
		if p == nil {
			break
		}
		p = p.next[c]
	}
	return p.ID
}

func DepthFirstTraverse(t *TrieNode, result *[]string, current *string) {
	if t == nil {
		return
	}

	if t.ID != -1 {
		*result = append(*result, *current)
	}
	for k, v := range t.next {
		*current += string(k)
		DepthFirstTraverse(v, result, current)
		*current = (*current)[:len(*current)-1]
	}
}

func (t *TrieNode) SearchPrefix(s string) []string {
	p := t
	prefix := ""
	for i := range s {
		var c byte = s[i]
		prefix += string(c)
		if p == nil {
			break
		}
		p = p.next[c]
	}

	if p == nil {
		return nil // No prefix found !
	}

	result := make([]string, 0)
	DepthFirstTraverse(p, &result, &prefix)
	return result
}

func (t *TrieNode) Remove(s string) {
	if t == nil {
		return
	}

	p := t
	for i := range s {
		var c byte = s[i]
		if p.next[c] == nil {
			return // Cannot find specified word!
		}
		p = p.next[c]
	}

	p.ID = -1 // Pseudo remove, not freeing any memory
}

// func DepthFirstTraverse(t *TrieNode) {
// 	if t == nil {
// 		return
// 	}
// 	for k, v := range t.next {
// 		fmt.Print(string(k), " ")
// 		DepthFirstTraverse(v)
// 	}
// }

func main() {
	t := CreateNode()
	t.Insert("12345", 10)
	t.Insert("abc", 2)
	t.Insert("alphabet", 16)
	// DepthFirstTraverse(t)
	// fmt.Println()
	fmt.Println(t.Search("12345"))
	fmt.Println(t.SearchPrefix("a"))
	t.Remove("abc")
	fmt.Println(t.SearchPrefix("a"))
}
