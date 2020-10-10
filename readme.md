1. vscode生成c++配置文件
F1: Edit configuration

2. vscode修改c++代码格式
{ BasedOnStyle: Google, IndentWidth: 4,ColumnLimit: 120 }

https://stackoverflow.com/questions/45823734/visual-studio-code-formatting-for
https://clang.llvm.org/docs/ClangFormatStyleOptions.html
https://code.visualstudio.com/docs/getstarted/settings


2. 生成某一库的include(pacman安装的库,非vcpkg)
pkg-config --cflags-only-I gtkmm-3.0 |tr -s " " "\012" | sed -n 's/-I//gp'

tr使用：https://stackoverflow.com/questions/1469849/how-to-split-one-string-into-multiple-strings-separated-by-at-least-one-space-in

3. 生成库的链接(放入make文件中)
pkg-config --libs gtkmm-3.0

4. 二者均生成:
pkg-config --cflags-only-I --libs gtkmm-3.0

5. make命令
make test sourcename=hello 