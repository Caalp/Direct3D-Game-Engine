//#pragma once
//#include <type_traits>
//#include <memory>
//
//template <class U>
//void union_test(U const volatile&)
//{
//	
//	static_assert(std::is_union<U>::value, "only unions allowed as an argument");
//}
//
//template<class T, class U>
//T union_cast(U const& u)
//{
//	union_test(u);
//	usign pT = typename std::remove_reference<T>::type;
//	return std::forward<T>(*(pT const*)std::addressof(u));
//
//}template<class U>
//void union_test( U const volatile& ) {
//  static_assert( std::is_union< U >::value, "only unions allowed as an argument" );
//}
//template<class T, class U>
//T union_cast( U const& u ) {
//  union_test(u);
//  using pT = typename std::remove_reference<T>::type;
//  return std::forward<T>(*(pT const*)std::addressof(u));
//}
//template<class T, class U>
//T union_cast( U const&& u ) {
//  union_test(u);
//  using pT = typename std::remove_reference<T>::type;
//  return std::forward<T>(*(pT const*)std::addressof(u));
//}
//template<class T, class U>
//T union_cast( U&& u ) {
//  union_test(u);
//  using pT = typename std::remove_reference<T>::type;
//  return std::forward<T>(*(pT*)std::addressof(u));
//}
//
//
//
