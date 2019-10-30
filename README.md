# Git Talk
===============================================================================


## WeeK 1 웹파싱과 pull 의 시간비교
-----------------------------------------------------------------------------------------------


* 웹파싱

<details markdown="1">
<summary>웹파싱 코드</summary>

### 웹파싱

' using System;
using System.Linq;
using System.Text;
using System.Web;
using System.Net;
using agi = HtmlAgilityPack;
using System.Diagnostics;

namespace WebParsing
{
    class Program
    {
        static void Main(string[] args)
        {
            Stopwatch sw = new Stopwatch();
            WebClient wc = new WebClient
            {
                Encoding = Encoding.UTF8
            };
            try
            {
                sw.Start();
                string html = wc.DownloadString("https://github.com/noino0819/GitTalk");
                agi.HtmlDocument doc = new agi.HtmlDocument();
                doc.LoadHtml(html);
                Console.WriteLine(doc.GetElementbyId("readme").InnerText);
                sw.Stop();
                Console.WriteLine(sw.ElapsedMilliseconds.ToString() + "ms");
            }
            catch (NullReferenceException)
            {
                Console.WriteLine("html is null");
                return;
            }
            
        }
    }
' 

</details>

> <웹파싱의 시간측정 >
> 
> ![웹파싱](https://user-images.githubusercontent.com/54929601/67845950-b768f380-fb43-11e9-927d-23eb98058243.png)
> 
> 
> 웹파싱의 경우, 측정시간이 * 611ms 로 나타남.


* pull

<details markdown="1">
<summary>pull 코드</summary>

### pull

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
   clock_t start, end;
   clock_t total_start, total_end;

   total_start = clock();
   FILE *fp = fopen("./SETTING.txt", "rt");

   char remote_add[120] = "git remote add GitTalk https://github.com/";
   char ID[20];
   char password[20];
   char repository_name[50];
   
   if (fp == NULL){
      printf("SETTING.txt 파일이 없습니다.\n");
      return 0;
   }

   fscanf(fp, "%s", ID);
   fscanf(fp, "%s", password);
   fscanf(fp, "%s", repository_name);

   strcat(remote_add, ID);
   strcat(remote_add, "/");
   strcat(remote_add, repository_name);
   
   system(remote_add);
   start = clock();
   system("git pull GitTalk master:master");
   end = clock();
   system("git remote remove GitTalk");

   fclose(fp);
   total_end = clock();

   putchar('\n');
   printf("pull만 :  %f\n", (double) (end - start) / CLOCKS_PER_SEC);
   printf("전체 : %f\n", (double) (total_end - total_start) / CLOCKS_PER_SEC);

   return 0;


</details>

> <pull의 시간측정 >
> 
> ![pull](https://user-images.githubusercontent.com/54929601/67846031-de272a00-fb43-11e9-9947-69cff317b084.png)
> 
> pull의 경우, 측정시간이 * 16.102ms로 나타남.


측정 결과, 웹파싱보다 pull의 속도가 더 우세하게 나타남.
속도의 우수성과 Git Talk의 취지중 하나인
"Git을 활용하는 방법에 대한 이해"에 맞춰
웹파싱 대신 Git에 존재하는 명령어인 pull을 이용하기로 함.
