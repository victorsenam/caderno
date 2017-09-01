#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef int tA;
typedef null_type tB;
typedef tree<tA, tB, less<tA>, rb_tree_tag, tree_order_statistics_node_update> ord_set;
// map: tA -> tB com comparador less<tA>
// pode usar como um map normalmente
// s.find_by_order(k) :: retorna iterador para o k-esimo elemento (0-index) (ou s.end())
// s.order_of_key(x)  :: retorna a qtd de elementos estritamente menores que x
