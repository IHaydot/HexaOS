find ./ -iname "*.cpp" -type f -exec wc -l {} \; > lines.out
find ./ -iname "*.hpp" -type f -exec wc -l {} \; >> lines.out
find ./ -iname "*.asm" -type f -exec wc -l {} \; >> lines.out
find ./ -iname "*.s" -type f -exec wc -l {} \; >> lines.out                        