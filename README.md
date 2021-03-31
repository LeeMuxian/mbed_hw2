## (1)
我的低通濾波器選用的是4100(歐姆)的電阻以及47(nF)的電容，代入公式可以得到cut-off frequency大約是826(Hz)。而我的學號108061114相加之後取餘10會得出2。
我的做法是先用uLCD顯示出以白色為背景黑色為字體顏色的狀態顯示出現在的頻率選項(826Hz為預設頻率)，往上加一次加100Hz，往下減一次減100Hz。當我按下select的按鍵之後才會開始產生波形，因為選擇頻率是一個無窮迴圈，當按下select之後會break出這個無窮迴圈才進入產生波形的無窮迴圈。另外，我是用thread去取樣這個我產生的波形，邊產生波的同時邊取樣(平行執行)。

## (2)
以下這張圖是當我的頻率在cut-off frequency(大約826Hz)的時候通過低通濾波器的波形。
![image](https://user-images.githubusercontent.com/72603727/113179652-6f8f5400-9282-11eb-98ac-ef2835d64cdb.png)

以下這張圖是當我的頻率在cut-off frequency(大約826Hz)的時候尚未通過低通濾波器的波形。
![image](https://user-images.githubusercontent.com/72603727/113180357-3c00f980-9283-11eb-8bbf-3b9e7508067f.png)

以下這張圖是我對濾波過的cut-off frequency的波進行取樣的數值(僅擷取少部分數值)。
![image](https://user-images.githubusercontent.com/72603727/113182976-132e3380-9286-11eb-8b40-5c0f8ceb2bb7.png)

我在C++的code當中是設定總共取樣500次，經過測試發現取樣500次總共花費3秒，因此取樣週期約為0.006秒，取樣頻率則為166.6666667Hz。

以下是python code產生出來的圖形。
![image](https://user-images.githubusercontent.com/72603727/113182659-bcc0f500-9285-11eb-8c42-52cd95eed273.png)

因為x軸有其最大最小值的極限，因此無法得到一個週期的模樣。
