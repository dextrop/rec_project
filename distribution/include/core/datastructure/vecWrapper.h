#ifndef VEC_WRAPPER_H
#define VEC_WRAPPER_H 

#include <vector>
#include <complex>
//#include <core/logginlib.h>
#include <core/utils/fftwrapper/fftWrapper.h>
#include <algorithm>

using namespace std;

#define ITPP_EXPORT 
#define vec  vector<double>
#define bvec vector<bool>
#define ivec vector<int>
#define cvec vector<complex<double> >

#define Array vector
//#define it_assert_debug(a,b) if(!(a)){DEBUG_HIGH(b); exit(0);}
#define it_assert_debug(a,b) if(!(a)){exit(0);}
// #define it_assert_debug(a,b) if(!a){DEBUG_HIGH(b); exit(0);}
#define it_assert(a,b) if(!(a)){exit(0);}
#define it_error(a) exit(0);

//------------------newly added functions............................
//@brief : base condition for concatinating vectors
template <typename T>
void ConcatVectors (const std::vector<T>& input_vec)
{
}

//@brief : concatinating all the vectors for concatinating vectors
template <typename T, typename... Args >
void ConcatVectors ( std::vector<T>& to_vector, const std::vector<T>& from_vector, const Args&... args) {
  to_vector.reserve (to_vector.size() + from_vector.size());
  to_vector.insert(to_vector.end(), from_vector.begin(),from_vector.end());
  ConcatVectors (to_vector, args...);
}

//@brief : vec to vec multiplication
template <typename T>
void  VecVecMultiply (const std::vector<T>& first_input, const std::vector<T>& second_input, std::vector<T>& output)
{
  if (first_input.size() != second_input.size()) return;

  int output_size = first_input.size();
  output.resize(output_size);

  for (int i = 0; i < output_size; ++i)
  {
    output[i] = first_input[i] * second_input[i];
  }
  //other way
  // std::transform(first_input.begin(),first_input.end(),second_input.begin(),output.begin(),std::multiplies<>());
}

//@brief : vec to vec addition 
template<typename T>
void  VecVecAddn (const std::vector<T>& first_input, const std::vector<T>& second_input, std::vector<T>& output)
{
  //need to include static_assert if all this are going to happen in compile time
  if (first_input.size() != second_input.size()) return;

  int output_size = first_input.size();
  output.resize(output_size);

  for (int i = 0; i < output_size; ++i)
  {
    output[i] = first_input[i] + second_input[i];
  }
 //other way
 // std::transform(first_input.begin(),first_input.end(),second_input.begin(),output.begin(),std::plus<>());
}

//--------------------------------------------------------------------
//ivec to_ivec(const char *invalues);

//void resize_true(vector<vector<int> > &input, int size);

//void setZero(vector<vector<int> > &input);

//void setZero(vector<int> &input);

//vector<int> concat(vector<int> &v1,const vector<int> &v2);

//vec concat(vec v1,vec v2);

//vector<bool> mid_vec(const vector<bool> &input, int start, int nr);

//vector<int> mid_vec(const vector<int> &input, int start, int nr);

//void replace_mid_vec(vector<int> &input, int start,const vector<int> &replc);

//void replace_mid_vec(vector<bool> &input, int start, const vector<bool> &replc);

//inline int int2bits(int n);

//bvec dec2bin(int length, int index);

//bvec dec2bin(int index, bool msb_first);

//void dec2bin(int index, bvec &v);

//int bin2dec(const bvec &inbvec, bool msb_first=true);

//void elem_mult(vector<double> &input1, vector<double> &input2, vector<double> &output);

//void elem_mult(FFT_COMPLEX_DATA_TYPE* input1, FFT_COMPLEX_DATA_TYPE* input2, FFT_COMPLEX_DATA_TYPE* output, int size);

void concatVectors(vector<double> &vector1, vector<double> &vector2);

//void addTwoVec(vec &data1, vec &data2, vec &output , double dividefactor = 1.0);

vector<double> getSubVector(vector<double> &input, int startIndex, int endIndex);

vector<complex<double> > getSubVector(vector<complex<double> > &input, int startIndex, int endIndex);

vector<bool> getSubVector(vector<bool> &input, int startIndex, int endIndex);

vector<int> getSubVector(vector<int> &input, int startIndex, int endIndex);

#endif
