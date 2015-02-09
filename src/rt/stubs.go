// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package runtime

import "unsafe"

// Declarations for runtime services implemented in C or assembly.

const ptrSize = 4 << (^uintptr(0) >> 63) // unsafe.Sizeof(uintptr(0)) but an ideal const
const regSize = 4 << (^uintreg(0) >> 63) // unsafe.Sizeof(uintreg(0)) but an ideal const

// Should be a built-in for unsafe.Pointer?
//go:nosplit
func add(p unsafe.Pointer, x uintptr) unsafe.Pointer {
	return unsafe.Pointer(uintptr(p) + x)
}

func getg() *g

// defined in sys_$GOOS_$GOARCH.s
func read(fd int32, p unsafe.Pointer, n int32) int32
func close(fd int32) int32

func exit(code int32)
func nanotime() int64
func usleep(usec uint32)

func mmap(addr unsafe.Pointer, n uintptr, prot, flags, fd int32, off uint32) unsafe.Pointer
func munmap(addr unsafe.Pointer, n uintptr)

//go:noescape
func write(fd uintptr, p unsafe.Pointer, n int32) int32

//go:noescape
func open(name *byte, mode, perm int32) int32

func madvise(addr unsafe.Pointer, n uintptr, flags int32)
