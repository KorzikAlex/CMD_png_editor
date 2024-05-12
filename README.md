<div align="center">
    <h1><b>CMD PNG EDITOR</b></h1>
    <h2><i>Курсовая работа по работе с изображениями</i></h2>
</div> 
Данная программа может:

1. Рисовать линию по заданным координатам, линия может быть разной толщины и цвета.
2. Отражать область изображения по определённой оси.
3. Рисовать пентаграмму в круге с заданными координатами центра, радиуса.

Чтобы собрать программу и запустить её, введите команды в терминале:

```shell
make
```

Чтобы проверить работоспособность программы, напишите данную команду:

```shell
./cw
```

Данная команда ввернёт вам данную справку:

```text
Usage: cw [OPTIONS]
OPTIONS:
-h, --help - print information about flags
--info - print information about PNG file
-i, --input <argument> - set input file name
 -o, --output <argument> - set output file name
--line <arguments> - set line drawing mode
        --start <x.y> - set start point of line
        --end <x.y> - set end point of line
        --color <r.g.b> - set color of line
         --thickness <argument> - set thickness of line
--mirror <arguments> - set mirror mode
         --axis <argument> - set axis of mirror (must me 'x' or 'y')
        --left_up <x.y> - set left_up point of mirror's edge
        --right_up <x.y> - set right_up point of mirror's edge
--pentagram <arguments> - set pentagram in circle mode
        --center <x.y> - set center point of pentagram
        --radius <argument> - set radius of pentagram
        --color <r.g.b> - set color of pentagram
        --thickness <argument> - set thickness of pentagram
```

./cw --input <input_file> --info
Данная команда вернёт в консоль информацию об изображении.

Входным файлом также будет считаться последний введённый вами аргумент
Пример:
Если вы не указали файл для сохранения, то он будет называть по умолчанию "out.png".
Фа

