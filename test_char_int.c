#include <stdio.h>

int main(int argc, char const *argv[]) {

  char a =0x00, b=0x01, big =0x30;
  printf("%c , %c \n", a,b);

  printf("%c", big);

  printf("is big <  a?: \n");
  if(big<a){
    printf("yes it is \n");
  }else{
    printf("no its not \n");
  }

  int a1 = (int)a, b1 = (int)b;
  int sum = a1 + a1 + b1 + b1;
  printf("%d, %d\n", a1,b1);
  printf("sum: %d\n", sum);
  return 0;
}
