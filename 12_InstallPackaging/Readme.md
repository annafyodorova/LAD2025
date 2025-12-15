Команды запуска 

```
autoreconf -fisv
```

```
./configure --prefix $PWD
```

```
make
```

```
make install
```

Для запуска программы 

```
./guess
```

Запуск с переводом 

```
LC_ALL=ru_RU.UTF-8 ./guess
```


Запуск с римскими числами 

```
./guess -r
```


Сообщение о подсказке

```
./guess --help
```


```
./guess --help-md
```

Генерация документации 

```
doxygen
```