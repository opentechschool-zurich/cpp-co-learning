#include <iostream>

using namespace std;

/**
 * @param v pointer to the input array (two elements)
 * @param w pointer to the output array (two elements)
 * @param k pointer to an array of four ints with the keys for the encryption
 */
template<typename T>
void encipher(const T *const v, T *const w, const T * const k)
{
     // static_assert(sizeof(int)==4,"size of int wrong for TEA");

     T y = v[0];
     T z = v[1];
     T sum = 0;
     const T delta = 0x9E3779B9;

     for (unsigned int n = sizeof(T) * 8; n-->0; ) {
         y += (z<<4 ^ z>>5) + z^sum + k[sum&3];
         sum += delta;
         z += (y<<4 ^ y>>5) + y^sum + k[sum>>11 & 3];
     }
     w[0]=y;
     w[1]=z;
}

template<typename T>
void decipher(const T *const v, T *const w, const T * const k)
{
	// static_assert(sizeof(int)==4,"size of int wrong for TEA");

	T y = v[0];
	T z = v[1];
	T sum = 0xC6EF3720;
	const T delta = 0x9E3779B9;

	// sum = delta<<5, in general sum = delta * n
    for (unsigned int n = sizeof(T) * 8; n-- > 0; ) {
        z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum&3];
	}
	w[0]=y;
	w[1]=z;
}

int main(){
    unsigned int cleartext[] = {1000, 2000};
    unsigned int ciphertext[2];
    unsigned int key[] = {1, 2, 3, 4};
    unsigned int decipheredtext[2];
    // unsigned long cleartext[] = {1000, 2000};
    // unsigned long ciphertext[2];
    // unsigned long key[] = {1, 2, 3, 4};
    // unsigned long decipheredtext[2];
    encipher(cleartext, ciphertext, key);

    cout << ciphertext[0] << " " << ciphertext[1] << endl;

    decipher(ciphertext, decipheredtext, key);

    cout << decipheredtext[0] << " " << decipheredtext[1] << endl;
    return 0;
}
