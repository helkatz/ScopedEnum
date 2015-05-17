# ScopedEnum
###Version
1.0.0

SCOPED_ENUM declares a scoped enum with the following features
* use toString to get a string literal of the actual enum value
* enum can only be used with full qualified name that allows the declaration of enums
  in the same scope with same enum values

the following declaration of the two enums causes an compiler error
```
enum e1 {
	A,
	B
}
enum e2 {
	A, // compiler error
	C
}
```
the following declaration of the two enums are allowed
```
SCOPED_ENUM(e1,
	A,
	B
);
SCOPED_ENUM(e2,
	A,
	C
);
```
usage simply delare like an enum
```
SCOPED_ENUM(eTest,
	A=1,
	B=3,
	C=5,
	D,
	EValue = 10,
	FValue
)

eTest e1 = eTest::EValue;
cout << e1.toString();
prints out EValue(10)
cout << e1;
prints out 10
```


