# Git Talk
===============================================================================


## WeeK 1 웹파싱과 pull 의 시간비교
-----------------------------------------------------------------------------------------------


* 웹파싱

<details markdown="1">
<summary>상세코드</summary>

### 웹파싱

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

> 
> ![웹파싱](https://user-images.githubusercontent.com/54929601/67845950-b768f380-fb43-11e9-927d-23eb98058243.png)
> 
> 
> 웹파싱의 경우, 측정시간이 * 611ms 로 나타남.


* pull

> <pull의 시간측정 코드>
> 
> ![pull](https://user-images.githubusercontent.com/54929601/67846031-de272a00-fb43-11e9-9947-69cff317b084.png)
> 
> pull의 경우, 측정시간이 * 16.102ms로 나타남.


측정 결과, 웹파싱보다 pull의 속도가 더 우세하게 나타남.
속도의 우수성과 Git Talk의 취지중 하나인
"Git을 활용하는 방법에 대한 이해"에 맞춰
웹파싱 대신 Git에 존재하는 명령어인 pull을 이용하기로 함.
