### FULL-MONI フルモニ
[Visit Page](https://blog.goo.ne.jp/nacci_tomoya/e/70d95214c48fda25100e8677de141ad6)
![fm1](PIC/fm1.png)
##１．フルモニとは
　フルコンモニターの略称で、「フルモニ」。
　各種フルコン（対応機種随時予定）やＤＥＦＩのコントロールユニットⅠ/Ⅱから取得したデータを
　３．５インチＴＦＴ液晶に数値やグラフとしてリアルタイム表示します。

　各データの取得は、
　フルコンからのデータは、ＣＡＮまたはＲＳ２３２Ｃ信号ケーブルを接続し、
　ＤＥＦＩコントロールユニットⅠ/Ⅱからのデータは、
　フルモニ専用のメータリンクケーブルを接続することで、データを受信します。

　表示データはそれぞれの表示選択や、ピークホールド表示、ワーニング表示を行います。
　※表示データの内容やその他機能詳細については、今後のファームウェア設計により随時追加することとします。

##２．設計概要
　基板　　…　３．５インチＴＦＴ液晶を備えた基板を設計する。
　ケース　…　タカチ電機工業製ＬＣＳ形シリコンケース付プラスチックケースを使用。
　　　　　　　　液晶、ＬＥＤ及び入力端子部分の切削加工を行う。

##３．ハードウェア仕様
　・１２Ｖバッテリー車向け制御電源（ＤＣ＋４．７５～＋３２Ｖ　→　内部電源＋３．３Ｖ）
　・タッチパネルＩＦ付３．５インチＴＦＴ液晶
　・液晶バックライト用電源(調光機能付)
　・ＣＰＵ　ルネサステクノロジ　Ｈ８ＳＸ１６５５　４８ＭＨｚ
　・外部ＳＲＡＭ　４Ｍｂｉｔ（おもに液晶用ビデオバッファ用途）
　・ＣＡＮ２．０Ｂ送受信　　　１チャンネル
　・ＲＳ２３２Ｃ送受信　　　　１チャンネル（ＦＣロガー接続選択機能付）
　・ＤＥＦＩ用Ｉ／Ｆ受信のみ　１チャンネル
　・超高輝度ＬＥＤ（赤・橙）
　・ケース内ブザー
　・タッチパネルＩ／Ｆ
　・ＳＰＩフラッシュＲＯＭ　４ｋｂｉｔ

##４．回路設計
　２０１１年９月２７日更新
　＜回路図はこちら＞
　※ライセンスはこちらをご覧ください

##５．基板設計
　２０１１年９月２７日更新
　＜基板図はこちら＞
　※ライセンスはこちらをご覧ください

##６．基板作成仕様
　・外形１３０．０ｍｍ×６６．０ｍｍ（但し外形はルーター加工特殊形状）
　・板厚１．６ｍｍ
　・ＦＲ４(ガラスエポキシ)
　・構成　４層（信号２層/電源２層）
　・部品実装　片面　白色
　・レジスト　両面　黒色
　・最小パタン幅０．２ｍｍ／最小クリアランス０．２ｍｍ
　・最小穴径０．５ｍｍ
　・無電解金フラッシュ仕上げ
