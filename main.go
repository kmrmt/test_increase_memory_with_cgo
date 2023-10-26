package main

// #cgo LDFLAGS: -L. -ltest -lstdc++
// #include "test.h"
import "C"
import "runtime"

func main() {
	const (
		dim  int = 128
		size int = 1000000
	)

	C.header()

	vectors := make([]float32, dim*size)
	for i := 0; i < size; i++ {
		vectors[i*dim] = float32(i)
	}

	pinner := &runtime.Pinner{}
	for n := 0; n < 100; n++ {
		ids := make([]C.size_t, size)
		C.stat(C.CString("init"))
		for i := 0; i < size; i++ {
			ptr := &vectors[i*dim]
			pinner.Pin(ptr)
			ids[i] = C.insert((*C.float)(ptr), C.size_t(dim))
			pinner.Unpin()

		}
		C.stat(C.CString("insert"))

		for i := 0; i < size; i++ {
			C.remove_(ids[i])
		}
		C.stat(C.CString("remove"))
	}

	C.stat(C.CString("finish"))
}
