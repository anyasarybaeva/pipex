# pipex

Цель проекта создать аналог Unix pipe
---
## Использование
```bash
    make
```
```bash
    make bonus
```
---
## Основная часть
Пример работы программы:
```bash
  ./pipex file1 cmd1 cmd2 file2
```
Программа принимает 4 аргумента:
* file1 и file2 имя файлов.
* cmd1 и cmd2 это команды терминала.

Вывод программы должен соответстовать:
```bash
  ./pipex < file1 | cmd1 | cmd2 ... |cmdn > file2
```
---
## Бонусная часть
Обработка нескольки pipe.
* Пример запуска программы:
```bash
  ./pipex file1 cmd1 cmd2 ... cmdn file2
```
* Резульат должен соответствовать:
```bash
  ./pipex < file1 | cmd1 | cmd2 ... |cmdn > file2
```


