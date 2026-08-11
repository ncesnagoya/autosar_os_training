# AppMode 演習のシミュレーション実行

athrill2 は起動時に DIP スイッチ入力である PPR0 をリセットするため、起動前に設定した DIP スイッチ状態は消去されます。
このため、シミュレーションでは athrill2 のリセット後、実行開始前に使用するスイッチを指定します。

## 使い方

```sh
make exe DSW=1       # AppMode1（task1 のみ）
make exe DSW=2       # AppMode2（task2 のみ）
make exe             # AppMode3（task1 と task2）
```

複数のスイッチを ON にする場合は、`make exe DSW="1 3"` のように空白区切りで指定できます。

## 手動で実行する場合

`make exe` 相当の操作を手動で行う場合は、まず athrill2 を対話モードで起動します。

```sh
athrill2 -c1 -i -d device_config.txt -m memory.txt atk2-sc1
```

`[DBG>` プロンプトで停止している間に、別の端末でリポジトリのルートから次のように DIP スイッチを設定します。その後、athrill2 側で `c` を入力して実行を開始します。

```sh
sh tools/dsw.sh dio_tools/dio.bin 1 on
```

`dsw.sh` の書式は次のとおりです。状態には `on` / `off` のほか、`1` / `0` も指定できます。

```text
tools/dsw.sh <dio.bin へのパス> <1-4> <on|off|1|0>
```
