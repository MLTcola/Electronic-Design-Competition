#ifndef __FFT16_H__  
#define __FFT16_H__  
  
typedef struct mycomplex //复数类型  
{  
  float real;       //实部  
  float imag;       //虚部  
}mycomplex;  
  
#define PI 3.1415926535897932384626433832795028841971  
  
  
///////////////////////////////////////////  
void conjugate_mycomplex(int n,mycomplex in[],mycomplex out[]);  
void c_plus(mycomplex a,mycomplex b,mycomplex *c);//复数加  
void c_mul(mycomplex a,mycomplex b,mycomplex *c) ;//复数乘  
void c_sub(mycomplex a,mycomplex b,mycomplex *c); //复数减法  
void c_div(mycomplex a,mycomplex b,mycomplex *c); //复数除法  
void fft(int N,mycomplex f[]);//傅立叶变换 输出也存在数组f中  
void ifft(int N,mycomplex f[]); // 傅里叶逆变换  
void c_abs(mycomplex f[],float out[],int n);//复数数组取模  
////////////////////////////////////////////  
#endif  
