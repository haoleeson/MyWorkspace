## 编译命令
### 1
g++ -DHAVE_CONFIG_H -I. -I.. -I .. -g -DNDEBUG  -ansi -fPIC -std=c++11 -Wall -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Werror -Wextra -Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winvalid-pch -Wlong-long -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wno-aggregate-return -Wno-padded -Wno-switch-enum -Wno-unused-parameter -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=3 -Wswitch -Wswitch-default -Wunreachable-code -Wunused -Wvariadic-macros -Wno-write-strings -Wno-missing-format-attribute -Wno-long-long -Wdate-time -D_FORTIFY_SOURCE=2 -g -DNDEBUG  -ansi -fPIC -std=c++11 -Wall -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Werror -Wextra -Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winvalid-pch -Wlong-long -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wno-aggregate-return -Wno-padded -Wno-switch-enum -Wno-unused-parameter -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=3 -Wswitch -Wswitch-default -Wunreachable-code -Wunused -Wvariadic-macros -Wno-write-strings -Wno-missing-format-attribute -Wno-long-long -g -O2 -fdebug-prefix-map=/sonic/src/sonic-swss-common=. -fstack-protector-strong -Wformat -Werror=format-security -c -o logctl.o `test -f 'logctl_test.cpp' || echo './'`logctl_test.cpp


### 2
g++ -DHAVE_CONFIG_H -I. -I.. -I src/hiredis/hiredis-0.14.0/debian/libhiredis-dev/usr/include  -g -DNDEBUG  -ansi -fPIC -std=c++11 -Wall -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Werror -Wextra -Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winvalid-pch -Wlong-long -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wno-aggregate-return -Wno-padded -Wno-switch-enum -Wno-unused-parameter -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=3 -Wswitch -Wswitch-default -Wunreachable-code -Wunused -Wvariadic-macros -Wno-write-strings -Wno-missing-format-attribute -Wno-long-long -Wdate-time -D_FORTIFY_SOURCE=2 -g -DNDEBUG  -ansi -fPIC -std=c++11 -Wall -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Werror -Wextra -Wfloat-equal -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winvalid-pch -Wlong-long -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wno-aggregate-return -Wno-padded -Wno-switch-enum -Wno-unused-parameter -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=3 -Wswitch -Wswitch-default -Wunreachable-code -Wunused -Wvariadic-macros -Wno-write-strings -Wno-missing-format-attribute -Wno-long-long -g -O2 -fdebug-prefix-map=/sonic/src/sonic-swss-common=. -fstack-protector-strong -Wformat -Werror=format-security -c -o logctl.o `test -f 'logctl_test.cpp' || echo './'`logctl_test.cpp

### 3
g++ -g -I src/hiredis/hiredis-0.14.0/debian/libhiredis-dev/usr/include -I src/sonic-swss-common -I src/sonic-swss-common/common -std=c++17 -o logctl_test.o ./logctl_test.cpp src/sonic-swss-common/common/dbconnector.cpp src/sonic-swss-common/common/redisclient.cpp src/sonic-swss-common/common/logger.cpp src/sonic-swss-common/common/redisreply.cpp src/sonic-swss-common/common/rediscommand.cpp src/sonic-swss-common/common/producerstatetable.cpp src/sonic-swss-common/common/select.cpp src/sonic-swss-common/common/consumerstatetable.cpp 

# Makefile.am 生成步骤

## 1. ./autogen.sh
```shell
#!/bin/bash

libtoolize --force --copy &&
autoreconf --force --install -I m4
rm -Rf autom4te.cache
```

## 2. ./configure
## 3. make

参考：
- [关于Makefile,Makefile.in,Makefile.am,Configure功能及相互关系的问题](https://blog.csdn.net/weixin_34205826/article/details/85943497)