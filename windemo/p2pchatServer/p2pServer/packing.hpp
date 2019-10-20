#pragma once
//https://gist.github.com/PhilCK/1534763

/*
	 Packing:
	 Cross platform way of ignore the default packing from the compiler.
	 I use this for accessing file headers such as bitmaps etc.
	 Example:

	 PACKED(
	 struct Foo { class details };
	 )
 */

#ifdef __GNUC__
#define PACKED( class_to_pack ) class_to_pack __attribute__((__packed__))
#else
#define PACKED( class_to_pack ) __pragma( pack(push, 1) ) class_to_pack __pragma( pack(pop) )
#endif
/*
PACKED(
  struct Bar
{
  float baz;
  float boo;
};
)

*/

