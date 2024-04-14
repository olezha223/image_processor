# Графический процессор

Данный проект является консольным приложением на языке C++,
позволяющее применять к изображениям различные фильтры, аналогичные фильтрам в популярных графических редакторах.

## Поддерживаемый формат изображений

Входные и выходные графические файлы должны быть в формате [BMP](http://en.wikipedia.org/wiki/BMP_file_format).

Формат BMP поддерживает достаточно много вариаций, но в этом задании будет использоваться
24-битный BMP без сжатия и без таблицы цветов. Тип используемого `DIB header` - `BITMAPINFOHEADER`.

Пример файла в нужном формате есть в статье на Википедии [в разделе "Example 1"](https://en.wikipedia.org/wiki/BMP_file_format#Example_1)
и в папке [test_script/data](test_script/data).

## Формат аргументов командной строки

Описание формата аргументов командной строки:

```shell
{имя программы} {путь к входному файлу} {путь к выходному файлу}
[-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...]
[-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ...
```

При запуске без аргументов программа выводит справку.

### Пример
```shell
./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5
```

В этом примере
1. Загружается изображение из файла `input.bmp`
2. Обрезается до изображения с началом в верхнем левом углу и размером 800х600 пикселей
3. Переводится в оттенки серого
4. Применяется размытие с сигмой 0.5
5. Полученное изображение сохраняется в файл `/tmp/output.bmp`

Список фильтров может быть пуст, тогда изображение будет сохранено в неизменном виде.
Фильтры применяются в том порядке, в котором они перечислены в аргументах командной строки.

## Список фильтров и описание аргументов

### Crop
Обрезает картинку, отсчитывая от правого верхнего угла. Принимает 2 целочисленных аргумента: ширина и высота.
В командной строке:
```shell
-crop 200 300
```
### GrayScale
Переводит картинки в черно-белый формат. Не принимает аргументов.
В командной строке:
```shell
-gs
```
### Negative
Переводит картинку в негатив. Не принимает аргументов.
В командной строке:
```shell
-neg
```
### Sharpening
Повышает резкость картинки. Не принимает аргументов.
В командной строке:
```shell
-sharp
```
### EdgeDetection
Выделяет границы на изображении. Принимает на вход число от 0 до 100. 
Пиксели со значением, превысившим его, окрашиваются в белый, остальные – в черный.
В командной строке:
```shell
-edge 0.6
```
### GaussianBlur
Производит размытие картинки. Принимает на вход один аргумент больше 0, который будет служить стандартным 
отклонением нормального распределения. Чем больше значение аргумента, тем сильнее размытие.
В командной строке:
```shell
-blur 3.2
```
### Дополнительный фильтр SickEye!
С помощью данного фильтра вы можете перевести картинку в психоделические цвета, 
а также добавите эффект раздвоения изображения. Фильтр принимает на вход два аргумента, которые должны принимать значение от 0 до 99.
Первый аргумент - это процент раздвоения картинки по вертикали, второй - по горизонтали.
В командной строке:
```shell
-sick 2 3
```
