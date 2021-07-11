package main

import (
	"fmt"
	"os"
)

func singleChar(c byte) int {
	if c == '*' {
		return 9
	}
	if c >= '1' {
		return 1
	}
	return 0
}

func doubleChar(s string) int {

	c0, c1 := s[0], s[1]

	if c0 == '1' {

		if c1 == '*' {
			return 9
		}
		return 1
	}

	if c0 == '2' {

		if c1 == '*' {
			return 6
		}
		if c1 <= '6' {
			return 1
		}
		return 0
	}

	if c0 == '*' {

		if c1 == '*' {
			return 15
		}
		if c1 <= '6' {
			return 2
		}
		return 1
	}

	return 0
}

func numDecodings(s string) int {

	M := 1000000007
	n := len(s)

	if n == 1 {
		return singleChar(s[n-1])
	}

	memo := make([]int, n)

	memo[n-1] = singleChar(s[n-1])
	memo[n-2] = doubleChar(s[n-2:n]) + singleChar(s[n-2])*singleChar(s[n-1])
	for ii := n - 3; ii >= 0; ii-- {
		memo[ii] = (singleChar(s[ii])*memo[ii+1] + doubleChar(s[ii:ii+2])*memo[ii+2]) % M
	}

	return memo[0]
}

type Testcase struct {
	input    string
	expected int
}

func (tt Testcase) Test() bool {
	actual := numDecodings(tt.input)
	fmt.Printf("%s expects %v got %v\n", tt.input, tt.expected, actual)
	return tt.expected == actual
}

func main() {

	testcases := []Testcase{
		{"*", 9},
		{"1*", 18},
		{"2*", 15},
		{"**", 96},
		{"***", 999},
	}

	for _, tt := range testcases {
		if !tt.Test() {
			os.Exit(1)
		}
	}
}
