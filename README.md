# QTSearch_testHW
Реализовать многопоточный поисковик слова (фразы) в текстовых файлах (пусть будут с маской *.txt) с помощью Qt. Вывести список проверяемых файлов в таблицу, и указать сколько искомых фраз содержится в каждом файле.

Однооконное приложение на Qt.
Элементы управления:
- поле (QLineEdit) для задания каталога с текстовыми файлами. Подключить диалог для выбора директории.
- поле для указания искомой фразы.
- поле для указания количества потоков.
- кнопка начала поиска.
- некоторый лейбл для отображения статуса работы (например): простой (ожидание), поиск, поиск окончен.
- таблица с результатами (два столбца: имя файла, количество вхождений искомой фразы).

Работа:
- Выбираем каталог с текстовыми файлами, пишем искомую фразу, выставляем количество потоков для поиска. Если хоть одно поле не заполнено, поиск не начинается: кнопка заблокированна.

- По клику на кнопку поиска:
В поле статуса вписываем статус что начался поиск. Элементы управления, кроме таблицы и статуса блокируются на время поиска.

Сканируем каталог на наличие файлов, если каталог не существует - выдаём ошибку. Если файлов нет - завершаем поиск, таблица пустая (по статусу мы должны понять что поиск окончен).
(ЗАБЫЛА ПРО ВЫДАЧУ ОШИБКИ... В МОЕЙ РЕАЛИЗАЦИИ ВВОД КАТАЛОГА ВОЗМОЖЕН ТОЛЬКО ЧЕРЕЗ ДИАЛОГ)

В начале имена всех найденных файлов (*.txt) отображаем в таблице - в первой колонке, во второй колонке пишем что файл ожидает проверки.
Далее заданным количеством потоков надо сканировать файлы на наличие искомой фразы, и во вторую колонку вписывать результат: количество найденных фраз (сразу после обработки файла).
Предполагается, что будет создан некий пул потоков, с очередью.

- По окончанию обхода файлов: заблокированные элементы управления приводим в нормальное состояние, статус - соответствующий. Приложение должно быть готово для нового поиска.

Ограничения:

При поиске приложение не должно фризиться. Таблица во время поиска должна быть доступна для скроллинга и выделения элементов.
Для реализации достаточно Qt 5й версии. Проект должен быть на CMake.

![image](https://github.com/Ulyanushka/QTSearch_testHW/assets/71116920/dd03a569-1fff-4a35-bb36-9ca2f3a03b18)
![image](https://github.com/Ulyanushka/QTSearch_testHW/assets/71116920/51ed46db-2ddc-4959-8fd6-5d05fd492e2b)
![image](https://github.com/Ulyanushka/QTSearch_testHW/assets/71116920/3a3e026a-af1e-4001-ac6f-7709fe73c777)
![image](https://github.com/Ulyanushka/QTSearch_testHW/assets/71116920/2a72f97f-91ac-4941-8ae0-8d8657b6eae0)
