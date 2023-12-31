# Афентьев Кирилл Викторович
# Задача No4 / Системное программирование

## Как запускать:
Программа использует сборку с cmake, запускать нужно следующим образом:
```
mkdir build
cd build
cmake ..
make
./dirdiff
```
После этого запустится программа, и на экране появится предложение о вводе.

## Принятые проектные решения
Я решил использовать часть стандартной бибилиотеки filesystem, так как это современный C++ инструмент для работы с файловой системой.
Проект разбит на файлы-логические части, реализующие принцип ООП для разделения сущностей.
В проекте есть папка `include`, которая предоставляет API для использования проекта сторонними программами.
В задании требуется оценивать схожесть файлов. Я принял решение, что коэффициентом схожести буду считать отношение длины самой большой общей подстроки файлов к длине более длинного файла. Этот выбор обусловлен тем, что он примерно отражает наши интуитивные ожидания от коэффициента похожести, а также быстро считается. Хорошим вариантом было бы рассмотреть возможность использования метрик из биоинформатики, где часто возникает задача о выравнивании двух текстовых последовательностей с целью достижения их наибольшего посимвольного пересечения (эта задача еще лучше отражает инутитивную суть схожести), но алгоритмы, вычисляющие такие метрики, труднозатратны (не лучше, чем O(N^2), где N - длина более длинной строки). В нашем же случае, когда файлов много, и каждый из них может весь десятки мегабайт, такие решения будут работать непозволительно долго. В итоге, я посчитал, что выбранная метрика лучше всего балансирует между качеством и скоростью (ассимптотика её вычисления есть O(N*log(N))), поэтому решил использовать её.
