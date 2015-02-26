// Copyright 2015 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// This file encapsulates some of the odd characteristics of the ARM64
// instruction set, to minimize its interaction with the core of the
// assembler.

package arch

import "cmd/internal/obj/arm64"

var arm64Jump = map[string]bool{
	"B":    true,
	"BL":   true,
	"BEQ":  true,
	"BNE":  true,
	"BCS":  true,
	"BHS":  true,
	"BCC":  true,
	"BLO":  true,
	"BMI":  true,
	"BPL":  true,
	"BVS":  true,
	"BVC":  true,
	"BHI":  true,
	"BLS":  true,
	"BGE":  true,
	"BLT":  true,
	"BGT":  true,
	"BLE":  true,
	"CALL": true,
}

func jumpArm64(word string) bool {
	return arm64Jump[word]
}

func arm64RegisterNumber(name string, n int16) (int16, bool) {
	switch name {
	case "F":
		if 0 <= n && n <= 31 {
			return arm64.REG_F0 + n, true
		}
	case "R":
		if 0 <= n && n <= 30 {
			return arm64.REG_R0 + n, true
		}
	case "V":
		if 0 <= n && n <= 31 {
			return arm64.REG_V0 + n, true
		}
	}
	return 0, false
}
