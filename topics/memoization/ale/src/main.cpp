#include <map>
template <typename T, T(*calc)(T)>
class mem {
        std::map<T, T> mem_map;
    public:
        T operator()(T input)
        {
            typename std::map<T, T>::iterator it;
            it = mem_map.find(input);
            if (it != mem_map.end()) {
                return it->second;
            } else {
                T output = calc(input);
                mem_map[input] = output;
                return output;
            }
        }
};

int unity(int in) { return in; }
    
int main()
{
    mem<int, unity> mem_unity;
    int y;
    y = mem_unity(10);
}
