// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// +build ignore

/*

7a is a version of the Plan 9 assembler.  The original is documented at

	http://plan9.bell-labs.com/magic/man2html/1/8a

Go-specific considerations are documented at

	http://golang.org/doc/asm

Its target architecture is the AArch64, referred to by these tools as arm64.

*/
package main
