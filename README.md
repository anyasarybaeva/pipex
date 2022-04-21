# pipex

Цель проекта создать аналог unix pipe

<img width="205" alt="Снимок экрана 2022-04-22 в 00 49 27" src="https://user-images.githubusercontent.com/36243405/164557742-86b6cc8d-313a-4f55-9aac-f06721196f0e.png">

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


