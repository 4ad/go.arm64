// +build arm64

package runtime

import "unsafe"

var oldBreak uintptr

const mallocVerbose = true

func newobject(typ *_type) unsafe.Pointer {
	return unsafe.Pointer(malloc(typ.size, uintptr(typ.align)))
}

func malloc(size, align uintptr) uintptr {
	if oldBreak == 0 {
		oldBreak = brk(0)
	}
	if mallocVerbose {
		print("Allocating ", size, " bytes, align = ", align, ", brk = ", hex(oldBreak))
	}
	addr := round(oldBreak+size-1, align)
	oldBreak = addr + size
	if newBrk := brk(oldBreak); newBrk != oldBreak {
		panic("brk failed")
	}
	if mallocVerbose {
		println(", newbrk =", hex(oldBreak))
	}
	return addr
}

// round n up to a multiple of a.  a must be a power of 2.
func round(n, a uintptr) uintptr {
	return (n + a - 1) &^ (a - 1)
}
