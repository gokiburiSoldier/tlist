# 文档

## 安装

将内容下载到本地：
```bash
git clone https://github.com/gokiburiSoldier/tlist.git
```

复制到目录下：
```bash
sudo cp tlist.cpp tlist.h /usr/include/c++/版本号/bits
sudo cp tlist /usr/include/c++/版本号
```

## 使用

使用 `tlist<T>` 来生成一个链表，例如：

```c++
tlist<int> ls;
```

以 `ls` 作为示例，我们有：

| 方法名 | 参数 | 返回值 | 示例 |
| -- | -- | -- | -- |
| `tlist<T>::append` | 值，表示在链表末尾插入的值 | 无 | `ls.append(3372)` |
| `tlist<T>::insert` | 索引，值。将索引处替换为值，并且移动后面的元素 | 无 | `ls.insert(0, 3372)` |
| `tlist<T>::query` | 索引 | 索引处元素的引用 | `ls.query(0)` |
| `tlist<T>::remove` | 索引，表示要删除元素的索引 | 无 | `ls.remove(0)` |
