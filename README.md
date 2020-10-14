# Showcase App

## Applications

* [ORM - CPP](./orm-cpp)
* [Typeahead - Golang](./typeahead-golang)

---

## ORM C++
It presents a simple interface for an ORM (Object Relational Mapper) implemented in C++.

The goals of this design are:
* Present a clean and straightforward interface.
* Be used on the server side (concurrent).

The packages used are:
* CMake
* C++ 17
* Google Test
* Google Mock

---

## Typeahead - Golang
It's a server side implementation of a typeahead functionality using golang language programming. It uses Rest API in order to communicate with the server.

The typeahead functionality is understood as a suggestion list of values ordered by specific criteria.

The solution uses a radix tree, a queue, and a comparison logic of the "suggestion" structure. The radix tree is selected due to prefix string (not exact match) are required. The queue and the comparison logic are used to order by some criteria the returned list.

The packages used are:
* github.com/armon/go-radix
* github.com/gorilla/mux
