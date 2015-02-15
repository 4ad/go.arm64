// +build arm64

package runtime

import "unsafe"

var oldBreak uintptr

const mallocVerbose = false

func newobject(typ *_type) unsafe.Pointer {
	if oldBreak == 0 {
		oldBreak = brk(0)
	}
	if mallocVerbose {
		print("Allocating ", typ.size, " bytes, align = ", typ.align, ", brk = ", hex(oldBreak))
	}
	addr := round(oldBreak+uintptr(typ.size)-1, uintptr(typ.align))
	oldBreak = addr + typ.size
	if newBrk := brk(oldBreak); newBrk != oldBreak {
		panic("brk failed")
	}
	if mallocVerbose {
		println(", newbrk =", hex(oldBreak))
	}
	return unsafe.Pointer(addr)
}

// round n up to a multiple of a.  a must be a power of 2.
func round(n, a uintptr) uintptr {
	return (n + a - 1) &^ (a - 1)
}
