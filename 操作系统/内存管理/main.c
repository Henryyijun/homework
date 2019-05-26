#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#define N 6
void test_malloc() {
    char* a[N];
    for (int i = 0; i < N; i++) {
        a[i] = malloc(128 * 1024 * 1024);
    }
    int num;
    printf("输入一个数字后释放2,3,5号内存\n");
    scanf("%d", &num);
    free(a[1]);
    free(a[2]);
    free(a[4]);
    printf("输入一个数字后分配1024Mb内存\n");
    scanf("%d", &num);
    char *b = malloc(1024 * 1024 * 1024);

}
int main() {
   pid_t pid = getpid();
   printf("pid = %d\n", pid);
   test_malloc();
   while(1);
}