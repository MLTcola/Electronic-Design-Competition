#ifndef __FFT16_H__  
#define __FFT16_H__  
  
typedef struct mycomplex //��������  
{  
  float real;       //ʵ��  
  float imag;       //�鲿  
}mycomplex;  
  
#define PI 3.1415926535897932384626433832795028841971  
  
  
///////////////////////////////////////////  
void conjugate_mycomplex(int n,mycomplex in[],mycomplex out[]);  
void c_plus(mycomplex a,mycomplex b,mycomplex *c);//������  
void c_mul(mycomplex a,mycomplex b,mycomplex *c) ;//������  
void c_sub(mycomplex a,mycomplex b,mycomplex *c); //��������  
void c_div(mycomplex a,mycomplex b,mycomplex *c); //��������  
void fft(int N,mycomplex f[]);//����Ҷ�任 ���Ҳ��������f��  
void ifft(int N,mycomplex f[]); // ����Ҷ��任  
void c_abs(mycomplex f[],float out[],int n);//��������ȡģ  
////////////////////////////////////////////  
#endif  
