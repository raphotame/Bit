#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int fdr;
	int fdw;
	char buff[100];//입출력버퍼
	if(mkfifo("myfifo_w",0666)==-1)//쓰기 파이프라인 생성
	{
		puts("mkfifo_w fail!");
		exit(1);
	}
	if(mkfifo("myfifo_r",0666)==-1)//읽기 파이프라인 생성
	{
		puts("mkfifo_r fail!");
		exit(1);
	}
	fdw = open("myfifo_w", O_RDWR);
	fdr = open("myfifo_r", O_RDWR);
	while(1)//쓰기,읽기 반복
	{
		while(1)
		{
			puts("쓰기모드");
			gets(buff);//내용 입력받음
			write(fdw,buff,strlen(buff));//쓰기 파이프에 써라
			if(strcmp(buff,"--") == 0)//--는 읽기,쓰기 변환문자
				break;//--와 같다면 읽기모드로
			memset(buff,0,100);
		}
		while(1)
		{
			puts("읽기모드");
			memset(buff,0,100);
			read(fdr,buff,100);
			if(strcmp(buff,"--") == 0)//--와 같다면 읽기모드로
				break;
			printf("%s\n",buff);
		}
	}          
	close(fdr);
	close(fdw);
	return 0;
}
