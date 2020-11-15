# kgcvis
## 何これ
- KaGasanCanvasVISualizer
- ステップ処理の可視化用ライブラリ。
- 8時間コンとかで使いたいすね。
- よく使うのがc++なので、c++から叩いてhtmlで出力する。（重いぞ！）
## sample
[↓の出力結果](https://kagasan.github.io/kgcvis/result.html)

```cpp
#include "kgcvis.hpp"
using namespace std;

int main() {

    KGCVIS pages(400, 100);
    vector<int>Y;
    for (int d = 0; d < 360; d++) {
        double rad = -acos(-1) * d / 18;
        pages.drawCircle(30, 50, 25, 128, 128, 128, 1);
        pages.drawCircle(30 + 25 * cos(rad), 50 + 25 * sin(rad), 3, 255, 0, 0, -1);
        pages.drawLine(0, 50, 640, 50, 128, 128, 128, 1);
        pages.drawLine(30, 0, 30, 480, 128, 128, 128, 1);
        pages.drawLine(30 + 25 * cos(rad), 50 + 25 * sin(rad), 55, 50 + 25 * sin(rad), 255, 128, 128, 1);
        for(int t = 0; t < Y.size(); t++) {
            pages.drawCircle(55 + Y.size() - t - 1, Y[t], 2, 255, 128, 128, -1);
        }
        Y.push_back(50 + 25 * sin(rad));
        pages.drawString(30, 0, 20, "y = " + to_string(-sin(rad)), 0, 0, 0);
        pages.newPage();
    }
    pages.write();
    return 0;
}
```
