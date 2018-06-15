#include <algorithm>
using std::all_of; using std::find; using std::equal;
#include <numeric>
using std::accumulate;
#include <functional> 
using std::function;
#include <string> 
using std::string;
#include <functional>
#include <iterator>
using std::iterator_traits;

template<typename Iterator>
typename iterator_traits<Iterator>::value_type
Sum(Iterator front, Iterator back){
    using value_type = typename iterator_traits<Iterator>::value_type;
    value_type init(0);
    return accumulate(front, back, init);
}

template<typename Iterator>
typename iterator_traits<Iterator>::value_type
Product(Iterator front, Iterator back){
    using value_type = typename iterator_traits<Iterator>::value_type;
    value_type init(1);
    return accumulate(front, back, init, std::multiplies<value_type>());
}

template<typename Iterator, typename Function>
auto SumBy(Iterator front, Iterator back, Function f) -> decltype(f(*front)){
    using value_type = typename iterator_traits<Iterator>::value_type;
    using f_type = decltype(f(*front));
    f_type init(0);
    return accumulate(front, back, init, [&f](f_type x, value_type y){return x + f(y);});
}

template<typename Iterator, typename Function>
auto ProductBy(Iterator front, Iterator back, Function f) -> decltype(f(*front)){
    using value_type = typename iterator_traits<Iterator>::value_type;
    using f_type = decltype(f(*front));
    f_type init(1);
    return accumulate(front, back, init, [&f](f_type x, value_type y){return x * f(y);});
}


template<typename ForwardIterator, typename Function>
ForwardIterator MinBy(ForwardIterator front, ForwardIterator back, Function f){
    using value_type = typename iterator_traits<ForwardIterator>::value_type;
    return std::min_element(front, back, [&f](value_type x, value_type y){return f(x) <f(y);});
}

template<typename ForwardIterator,  typename Function>
ForwardIterator MaxBy(ForwardIterator front, ForwardIterator back, Function f){
    using value_type = typename iterator_traits<ForwardIterator>::value_type;
    return std::max_element(front, back, [&f](value_type x, value_type y){return f(x) < f(y);});
}

template<typename ForwardIterator, typename Predicate>
ForwardIterator KeepIf(ForwardIterator front, ForwardIterator back, Predicate p){
    using value_type = typename iterator_traits<ForwardIterator>::value_type;
    return std::remove_if(front, back, [&p](value_type item){return !p(item);});
}

/* 只能够用于string的序列 */
template<typename InputIterator>
string Join(InputIterator front, InputIterator back, const string &sep){
    using value_type = typename iterator_traits<InputIterator>::value_type;
    string init = *front++;
    return accumulate(front, back, init, [&sep](string x, value_type y){return x + sep + y;});
}

