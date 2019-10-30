# Git Talk
=============

## 웹파싱과 pull 의 시간비교
-------------------------

* 웹파싱

> 
> 
> <details markdown="1">
> <summary>접기/펼치기</summary>
> 
> ### <웹파싱 코드>

using System;
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


</details>

![웹파싱](./C:\Users\Owner\Desktop/웹파싱.png)


웹파싱의 경우, 측정시간이 N초로 나타남.

* pull

> <pull의 시간측정 코드>

pull의 경우, 측정시간이 N초로 나타남.


웹파싱과pull의 시간차이가 미세하기 떄문에, Git Talk의 취지중 하나인
"Git을 활용하는 방법에 대한 이해"에 맞춰
Git에 존재하는 명령어인 pull을 이용하기로 함.
